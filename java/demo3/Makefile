
JAR="/hadoop/share/hadoop/common/hadoop-common-2.6.0-cdh5.7.1.jar:/hadoop/share/hadoop/mapreduce/hadoop-mapreduce-client-core-2.6.0-cdh5.7.1.jar:/hadoop/share/hadoop/common/lib/hadoop-annotations-2.6.0-cdh5.7.1.jar:/hadoop/share/hadoop/common/lib/commons-cli-1.2.jar:/hadoop/share/hadoop/hdfs/lib/commons-logging-1.1.3.jar"

all:
	javac -classpath $(JAR)  demo.java -d . -Xlint:deprecation
	jar cvf demo.jar ./demo

clean:
	rm -rf demo
	rm -f demo.jar
	
run:
	hadoop jar demo.jar demo.demo
del:
	hadoop fs -rm -r /tmp
ls:
	hadoop fs -ls hadoop fs -ls /tmp/output
cat:
	hadoop fs -cat /tmp/output/part*
