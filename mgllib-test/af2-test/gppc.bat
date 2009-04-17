@echo *********************************************************************:
@REM dlltool --dllname mgllib.dll --input-def ../lib/mgllib.exp --output-lib mgllib.a

@REM g++ af2_test.cpp MwlAghFactory.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh ../lib/mgllib.lib ../lib/mwlagh.lib
g++ af2_test_1.cpp MwlAghFactory.cpp MwlAghWindow.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh

@REM g++ af2_test.cpp -I../include/mgl_header -I../AGH/include -I../mwl/mwlagh ../lib/mgllib.exp ../lib/mgllib.lib ../lib/mwlagh.lib