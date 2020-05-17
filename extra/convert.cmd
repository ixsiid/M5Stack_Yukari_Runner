echo off

set FFMPEG=%USERPROFILE%\Downloads\ffmpeg-20180421-e5ba5fa-win64-static\bin\ffmpeg.exe

for %%f in (%~dp0mov\*.mov) do (
    echo Convert: %%~nf
    mkdir %~dp0bmp\%%~nf
    %FFMPEG% -i %%f -f image2 -vcodec bmp -pix_fmt rgb565 -vf select='between^(n,100,120^)',setpts=PTS-STARTPTS,framestep=4 %~dp0bmp\%%~nf\%%08d.bmp
    rem -vf trim=start_frame=100:end_frame=132,framestep=4

)

exit
