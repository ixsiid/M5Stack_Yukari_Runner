const resources = require('./resources.json');
const path = require('path');
const fs = require('fs');

const header = fs.openSync(path.join(__dirname, 'src', 'Resources.h'), 'w');
const source = fs.openSync(path.join(__dirname, 'src', 'Resources.cpp'), 'w');
fs.writeSync(header, `\
#pragma once
#include <stdint.h>

class Resources {
	private:
		static const uint8_t _buffer[];
	public:`);

fs.writeSync(source, `\
#include "Resources.h"

const uint8_t Resources::_buffer [] = {
`);

let index = 0;
const keys = [];
const generateBmp = file => {
	const buffer = fs.readFileSync(file);
	if (buffer[0] != 66 || buffer[1] != 77) throw 'Not bitmap file'; // 66 := 'B', 77 := 'M'
	const bit = buffer[28] + (buffer[29] << 8);
	if (bit != 16) throw 'Only RGB565 bitmap';

	const header_size = buffer[10] + (buffer[11] << 8) + (buffer[12] << 16) + (buffer[13] << 24);
	const width = buffer[18] + (buffer[19] << 8) + (buffer[20] << 16) + (buffer[21] << 24);
	const height = buffer[22] + (buffer[23] << 8) + (buffer[24] << 16) + (buffer[25] << 24);

	for (let r = height - 1; r >= 0; r--) {
		const row_start = header_size + r * width * 2; // 2は16bitだから
		fs.writeSync(source, `	${
			buffer.slice(row_start, row_start + width * 2)
				  .toString('hex')
				  .replace(/([0-9a-f][0-9a-f])/g, '0x$1,')}\n`);
	}

	return buffer.length - header_size;
};

Object.entries(resources).forEach(async ([k, v]) => {
	const file = path.join(__dirname, v.path);

	if (v.type == 'bmp') {
		keys.push(['uint16_t', k, index + 0]);
		index += generateBmp(file);
	}
});

fs.writeSync(header, `
		${keys.map(([type, name]) => `static const ${type} * ${name}`).join(';\n\t\t')};
};
`);

fs.writeSync(source, `0 };

${keys.map(([type, name, i]) => `const ${type} * Resources::${name} = (${type} *)&Resources::_buffer[${i}]`).join(';\n')};
`);


fs.close(header, () => { });
fs.close(source, () => { });
