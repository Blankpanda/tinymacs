@echo on
 
SET deps=user32.lib Gdi32.lib
SET entry=..\src\win32_main.cpp ..\src\debugLogger.cpp ..\src\directory.cpp

cl /I ..\include %entry% /link /subsystem:windows %deps%  
