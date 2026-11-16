#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>


 //Retrieves and displays all records from the students table.
void getAllStudents(PGconn *conn){
     // Execute SELECT query
    PGresult *res = PQexec(conn, "SELECT * FROM students;");
    
    //check result/whether query executed successfully
    if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK){
        fprintf(stderr, "%s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    //Get the total number of rows returned
    int rows = PQntuples(res);

    printf("\nStudents:\n");

    //Display each student record
    for(int i = 0; i < rows; i++){
        printf("%s %s %s %s\n",
            PQgetvalue(res, i, 0),
            PQgetvalue(res, i, 1),
            PQgetvalue(res, i, 2),
            PQgetvalue(res, i, 3));
    }

    //Free memory from  query result
    PQclear(res);
}

//Inserts a new student record into the students table.
void addStudent(PGconn *conn, char *first_name, char *last_name, char *email, char *enrollment_date){
 
    const char *query = "INSERT INTO students (first_name, last_name, email, enrollment_date) VALUES ($1, $2, $3, $4)";

    // Stores function parameters in an array for PQexecParams
    const char *paramValues[4] = {
        first_name,
        last_name,
        email,
        enrollment_date
    };

     // Execute parameterized INSERT query
    PGresult *res = PQexecParams(conn, query, 4, NULL, paramValues, NULL, NULL, 0);

    //check result/whether query executed successfully
    if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK){
        fprintf(stderr, "%s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    //Free memory from  query result
    PQclear(res);
    printf("Student added successfully. \n");
}

//Updates the email address for a student with the specified student_id.
void updateStudentEmail(PGconn *conn, char *student_id, char *new_email){
    const char *query = "UPDATE students SET email = $1 WHERE student_id = $2";
    
 // Stores new email and student ID in an array for PQexecParams
    const char *paramValues[2] = {
        new_email,
        student_id
    };
 // Execute UPDATE query
    PGresult *res = PQexecParams(conn, query, 2, NULL, paramValues, NULL, NULL, 0);

    //check result/whether query executed successfully
    if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK){
        fprintf(stderr, "%s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    PQclear(res);
    printf("Email updated successfully. \n");
}

//Deletes the record of the student with the specified student_id.
void deleteStudent(PGconn *conn, char *student_id){
    const char *query = "DELETE FROM students WHERE student_id = $1";

 // Stores function parameters in an array for PQexecParams
    const char *paramValues[1] = {
        student_id
    };

  //Execute parameterized DELETE query
    PGresult *res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    //check result/whether query executed successfully
    if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK){
        fprintf(stderr, "%s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    PQclear(res);
    printf("Student deleted successfully. \n");
}



int main(){
   //establish connection to the PostgreSQL database
    PGconn *conn = PQconnectdb( //makes a new connection to the database server
        "host=localhost "
        "dbname=studentdb "
        "user=postgres "
        "password=momrules"
    );

    //Check that connection to database was successful

    if (PQstatus(conn) != CONNECTION_OK){
        printf("Connection failed.");
        return 1;
    };

    //Test CRUD operations
    getAllStudents(conn);
    addStudent(conn, "tendresse "umuhire "tendresseU@gmail.com", "2026-11-15");
    getAllStudents(conn);

    updateStudentEmail(conn, "4", "newemail@gmail.com");
    getAllStudents(conn);

    deleteStudent(conn, "2");
    getAllStudents(conn);

    Close data base connection
    PQfinish(conn);


}
