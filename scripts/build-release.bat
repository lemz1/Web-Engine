@echo off

call "vendor\premake\windows\premake5.exe" vs2022

call "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" Web-Engine.sln /p:Configuration=release
