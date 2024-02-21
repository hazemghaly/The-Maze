#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
/**
 * updateUser - update user inputs.
 * @conn: connection to database.
 * @up_user: User.
 * @score: user score.
*/
void updateUser(MYSQL *conn, const char *up_user, int level, int score)
{
char query[512];    /*Update the user's level and score*/
sprintf(query,
"UPDATE MAZE_DB.users SET level=%d, score=%d WHERE username='%s'",
level, score, up_user);
if (mysql_query(conn, query))
{
fprintf(stderr, "Error: %s\n", mysql_error(conn));
exit(1);
}
}
/**
 * insertUser - update user inputs.
 * @conn: connection to database.
 * @username: User.
*/
void insertUser(MYSQL *conn, const char *username)
{
char query[512];    /* Check if the user exists*/
MYSQL_RES *result;
sprintf(query,
"SELECT username FROM MAZE_DB.users WHERE username='%s'",
username);
if (mysql_query(conn, query))
	{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
	}
result = mysql_store_result(conn);
if (result == NULL)
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
if (mysql_num_rows(result) == 0) /* not exit so INSERT*/
{
sprintf(query,
"INSERT INTO MAZE_DB.users (username, level, score) VALUES ('%s', 1, 0)",
username);
if (mysql_query(conn, query))
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
	mysql_free_result(result);
}
if (mysql_num_rows(result) > 0)
{/* Username already exists*/
	fprintf(stderr, "Error: Username '%s' already exists\n", username);
	mysql_free_result(result);
}
}
/**
 * deleteUser - delete user inputs.
 * @conn: connection to database.
 * @del_user: User.
*/
void deleteUser(MYSQL *conn, const char *del_user)
{
	char query[512];

	sprintf(query, "DELETE FROM MAZE_DB.users WHERE username='%s'", del_user);
	if (mysql_query(conn, query))
	{
		fprintf(stderr, "Error: %s\n", mysql_error(conn));
		exit(1);
	}
}
/**
 * main - main.
*/
int main(void)
{
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char username[256], del_user[256], up_user[256], query[512];
char *server = "localhost", *user = "root", *password = "password";
conn = mysql_init(NULL);
if (conn == NULL)
{
	fprintf(stderr, "mysql_init() failed\n");
	exit(1);
}
if (!mysql_real_connect(conn,
"localhost", user,
password, "MAZE_DB", 0, NULL, 0))
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
if (mysql_query(conn,
"CREATE DATABASE IF NOT EXISTS MAZE_DB"))
{
	fprintf(stderr, "%s\n", mysql_error(conn));
	exit(1);
}
if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS MAZE_DB.users ("
"username VARCHAR(256) UNIQUE NOT NULL, "\
"level INT DEFAULT 1, "\
"score INT DEFAULT 0, "\
"created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "\
"updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"\
"ON UPDATE CURRENT_TIMESTAMP"\
")"))
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
updateUser(conn, up_user, 56, 6);
insertUser(conn, username);
sprintf(query,
"SELECT username ,level, score FROM MAZE_DB.users WHERE username='%s'",
username);
if (mysql_query(conn, query))
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
res = mysql_store_result(conn);
printf("After insert:\n");
while ((row = mysql_fetch_row(res)) != NULL)
{
	printf("%s|| Level: %s || Score: %s\n", row[0], row[1], row[2]);
}
mysql_free_result(res);
deleteUser(conn, del_user);
if (mysql_query(conn, "SELECT username, level, score FROM MAZE_DB.users"))
{
	fprintf(stderr, "Error: %s\n", mysql_error(conn));
	exit(1);
}
res = mysql_store_result(conn);
printf("After delete:\n");
while ((row = mysql_fetch_row(res)) != NULL)
{
	printf("%s|| Level: %s || Score: %s\n", row[0], row[1], row[2]);
}
mysql_free_result(res);
mysql_close(conn);/* Close connection*/
return (0);
}
