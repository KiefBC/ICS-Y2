-- Write a PL/SQL CircleArea with a given radius and computer the area of the circle.
SET SERVEROUTPUT ON

DECLARE
    pi CONSTANT NUMBER := 3.14159;
    radius NUMBER := 5;
    area NUMBER;

BEGIN

    area := pi * radius * radius;
    DBMS_OUTPUT.PUT_LINE('The area of the circle is ' || area);

    -- if radius is zero or less return area of zero
    IF radius <= 0 THEN
        DBMS_OUTPUT.PUT_LINE('The radius is zero or less, so the area is zero.');
    END IF;

END;



