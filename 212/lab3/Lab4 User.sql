CREATE USER c##lab4_user IDENTIFIED BY password;

GRANT CONNECT TO c##lab4_user;

DESCRIBE DUAL;
SELECT * FROM DUAL;
CREATE TABLE TEST AS SELECT * FROM DUAL;

GRANT RESOURCE TO c##lab4_user;
GRANT UNLIMITED TABLESPACE TO c##lab4_user;

CREATE PROFILE c##temp_user LIMIT
    PASSWORD_LIFE_TIME 5
    FAILED_LOGIN_ATTEMPTS 3
    PASSWORD_LOCK_TIME 1;

ALTER USER c##lab4_user PROFILE c##temp_user;

SELECT * FROM DBA_PROFILES WHERE PROFILE = 'C##TEMP_USER';

SELECT ACCOUNT_STATUS FROM DBA_USERS WHERE USERNAME = 'C##LAB4_USER';

CREATE USER c##lab4_user2 IDENTIFIED BY password;

GRANT CONNECT TO c##lab4_user2;

GRANT SELECT ON c##lab4_user.test TO c##lab4_user2;