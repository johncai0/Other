#include "mysql.h"
#pragma comment(lib,"libmysql") 
#define HOST "localhost" 
#define USERNAME "john" 
#define PASSWORD "john" 
#define DATABASE "john"
/*gcc -o mycli ./mysql.c -L/usr/lib64/mysql -lmysqlclient*/
void exe_sql(char* sql) { 
	MYSQL my_connection;
	int res,i;
	char text[1024];
	mysql_init(&my_connection);
	if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) 
	{
		mysql_autocommit(&my_connection, 0);
		printf("数据库执行exe_sql连接成功\n"); 
		mysql_query(&my_connection, "set names utf8");
		for (i=0;i<=1000;i++) {
			char value[56];
			sprintf(text,"insert into john_test_2000 (name,sex,age,password,txt)" 
				"value ('%djohn',%d, ROUND(round(rand(),4) * 10000),'pass%d',concat(md5(%d),%s,md5(%d)));",
				i,i%2?0:1,i,i,LTXT,i);
			res = mysql_query(&my_connection, text);
			if (res != 0) {
				printf("Error：[%d] %s\n",mysql_errno(&my_connection),mysql_error(&my_connection)); 
				mysql_close(&my_connection); 
			} 
			if (i%200 == 0) {
				mysql_commit(&my_connection);
                                printf("\rINFO: [%d] be inserted!",i);                                   
                                //printf("%d 行受到影响！\n", mysql_affected_rows(&my_connection)); 
                                //mysql_close(&my_connection); 
			}
		}
		printf("\rINFO: [%d] be inserted!\n",i);
		mysql_commit(&my_connection);
		mysql_close(&my_connection); 
	}
	else 
	{ 
		printf("数据库执行exe_sql连接失败！\n"); 
	} 
} 
void query_sql(char* sql) { 
	MYSQL my_connection;
	int res;
	MYSQL_RES *res_ptr;
	MYSQL_FIELD *field;
	MYSQL_ROW result_row;
	int row, column;
	int i, j;
	mysql_init(&my_connection); 
	if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, 
				DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {
		printf("数据库查询query_sql连接成功！\n"); 
		mysql_query(&my_connection, "set names utf8"); 
		res = mysql_query(&my_connection, sql); 
		if (res != 0) {
			printf("Error：[%d] %s\n",mysql_errno(&my_connection),mysql_error(&my_connection)); 
			mysql_close(&my_connection); 
		} else {
			res_ptr = mysql_store_result(&my_connection); 
			if (res_ptr) { 
				column = mysql_num_fields(res_ptr); 
				row = mysql_num_rows(res_ptr) + 1; 
				printf("查询到 %lu 行 \n", row); 
				for (i = 0; field = mysql_fetch_field(res_ptr); i++) 
					printf("%s\t", field->name); 
				printf("\n"); 
				for (i = 1; i < row; i++) { 
					result_row = mysql_fetch_row(res_ptr); 
					for (j = 0; j < column; j++) 
						printf("%s\t", result_row[j]); 
					printf("\n"); 
				} 
			} 
			mysql_close(&my_connection); 
		} 
	} 
} 
int main(int argc, char *argv[]) { 
	char *query; 
	char *exe = "insert into john_table values('1','john');"; 
	exe_sql(exe); 
	//query="select * from john_table;"; 
	//query_sql(query); 
	return 0; 
}
