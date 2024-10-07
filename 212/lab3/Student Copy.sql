create table NEW_STUDENT
(
    STUDENT_ID NUMBER not null
        constraint NEW_STUDENT_PK
            primary key,
    FIRST_NAME VARCHAR2(30),
    LAST_NAME  VARCHAR2(30)
)