@echo off
pushd %~dp0\..\
call C:\CTXEngine\Build\bin\premake5.exe vs2019
popd

pause