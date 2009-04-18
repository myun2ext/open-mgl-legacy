@echo *********************************************************************:
@REM dlltool --dllname mgllib.dll --input-def ../lib/mgllib.exp --output-lib mgllib.a

@REM g++ af2_test.cpp MwlAghFactory.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh ../lib/mgllib.lib ../lib/mwlagh.lib
@REM g++ af2_test_1.cpp MwlAghFactory.cpp MwlAghWindow.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh
@REM g++ af2_test_2.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh -L../lib/ -lmgllib ../lib/mgllib.lib ../lib/mwlagh.lib -mwindows
g++ af2_test_2.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh  -L./ -L../lib/mingw -lmgllib ../lib/mingw/libmgllib.a -mwindows

@REM g++ af2_test.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh ../lib/mgllib.exp ../lib/mgllib.lib ../lib/mwlagh.lib