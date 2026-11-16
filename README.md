NAME: Tendresse Umuhire
PROJECT: Database Interaction with PostgreSQL and Application Programming

DESCRIPTION: This program demonstrates CRUD operations using C and PostgreSQL.

REQUIREMENTS:

    PostgreSQL 18
    GCC compiler
    libpq
    Compile

SETUP:
    The application uses the following table:
        CREATE TABLE students (
            student_id SERIAL PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            enrollment_date DATE
        );
    With initial data:
        INSERT INTO students
        (first_name, last_name, email, enrollment_date)
        VALUES
        ('John', 'Doe', 'john.doe@example.com', '2023-09-01'),
        ('Jane', 'Smith', 'jane.smith@example.com', '2023-09-01'),
        ('Jim', 'Beam', 'jim.beam@example.com', '2023-09-02');

COMPILATION:

    gcc crudd.c \
    -I/Library/PostgreSQL/18/include \
    -L/Library/PostgreSQL/18/lib \
    -lpq \
    -o crudd

    where, 
        -I/Library/PostgreSQL/18/include tells the compiler where to find PostgreSQL header files such as libpq-fe.h.
        -L/Library/PostgreSQL/18/lib tells the linker where PostgreSQL libraries are located.
        -lpq links the program with PostgreSQL's client library.
        -o crudd specifies the name of the executable file.

RUN:

    ./crudd

NOTE: may require the following if on mac

    export DYLD_LIBRARY_PATH=/Library/PostgreSQL/18/lib:$DYLD_LIBRARY_PATH
    ./crudd


IMPLEMENTED FUNCTIONS:

    1. getAllStudents()
    Retrieves and displays all records from the students table using a SQL SELECT query.

    2. addStudent(first_name, last_name, email, enrollment_date)
    Inserts a new student record into the students table using a parameterized SQL INSERT query with PQexecParams().

    3. updateStudentEmail(student_id, new_email)
    Updates the email address of a student with the specified student_id using a parameterized SQL UPDATE query.

    4. deleteStudent(student_id)
    Deletes the student record associated with the specified student_id using a parameterized SQL DELETE query. 

PROGRAM:

    Should perform the following operations :
    Display all existing students
    Add a new student record
    Display all students 
    Update the new student's email address
    Display all students
    Delete a student record
    Display all students

EXTERNAL SOURCES:
    https://www.postgresql.org/docs/9.1/libpq.html
    https://www.youtube.com/watch?v=GWRh2S-laec
