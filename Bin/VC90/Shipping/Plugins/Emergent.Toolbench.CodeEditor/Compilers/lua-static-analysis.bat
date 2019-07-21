@echo off
luac5.1 -p -l "%~1" | lua5.1 globals.lua
