echo off

set FFMPEG=%USERPROFILE%\AppData\Local\bin\ffmpeg

for %%f in (%~dp0mov\*.mov) do (
    echo Convert: %%~nf
    mkdir %~dp0bmp\%%~nf
    %FFMPEG% -skip_frame nokey -i %%f -f image2 -vcodec bmp -pix_fmt rgb565 %~dp0bmp\%%~nf\%%08d.bmp
    rem -vf trim=start_frame=100:end_frame=132,framestep=4

)

exit
