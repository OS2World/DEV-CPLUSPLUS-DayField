@echo off
SET NAME=DAYFIELD
SET PROTO= 
SET PROTOH=
SET OPT=/Od
SET CDBG=/Zi
SET LDBG=/CO

if -%1- == -- goto make
if %1 == ? goto help

:two
if -%2- == -- goto make
if %2   == COMPILE goto three
if %2   == compile goto three
set PROTO=/Zg
set PROTOH=^> $*.h

:three
if -%3- == -- goto make
if %3   == MAKE goto four
if %3   == make goto four
touch *.c > nul
touch *.asm > nul

:four
if -%4- == -- goto make
if %4   == DEBUG goto five
if %4   == debug goto five
set CDBG=
set LDBG=

:five
if -%5- == -- goto make
if %5   == size  set OPT=/Os
if %5   == SIZE  set OPT=/Os
if %5   == speed set OPT=/Ot
if %5   == SPEED set OPT=/Ot
if %5   == MAX   set OPT=/Ox
if %5   == max   set OPT=/Ox

:make
make %name%

if -%1- == -- goto end
if %1 == notell goto end
if %1 == NOTELL goto end

if errorlevel 1 goto badpop 
popup " %NAME% built sucessfully"
goto end

:badpop
popup "%NAME% had problems" 
goto end

:help
echo bld [notell] [compile] [make] [debug]   [speed] 
echo     [tell]   [proto]   [full] [nodebug] [noopt]
echo     [?]                                 [size]
echo                                         [max]

:end
