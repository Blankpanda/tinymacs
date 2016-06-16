@echo on

SET deps=user32.lib Gdi32.lib
SET entry=win32_main.cpp

cl %entry% /link /subsystem:windows %deps%
