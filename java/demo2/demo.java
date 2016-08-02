
package demo;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;

import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class demo {

    public static class demoMapper extends Mapper<Object, Text, Text, Text> {

	Text str = new Text("map");
	public void map(Object key, Text value, Context context) throws IOException, InterruptedException {

	    System.out.println("map::" + value.toString());
	    context.write(value, str);
	}
    }

    public static class demoCombiner extends Reducer<Text, Text, Text, Text> {

	Text str = new Text("reduce1");
	public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {

	    for (Text value : values) {

		System.out.println("reduce1::" + key.toString() + "::" + value.toString());
		context.write(key, str);
	    }
	}
    }

    public static class demoReducer extends Reducer<Text, Text, Text, Text> {

	Text str = new Text("reduce2");
	public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {

	    for (Text value : values) {

		System.out.println("reduce2::" + key.toString() + "::" + value.toString());
		context.write(key, str);
	    }
	}
    }

    public static void main(String[] args) throws Exception {


	Configuration conf = new Configuration();
	Job job = Job.getInstance(conf, "demo");
	job.setJarByClass(demo.class);

	job.setMapperClass(demoMapper.class);
	job.setCombinerClass(demoCombiner.class);
	job.setReducerClass(demoReducer.class);

	job.setOutputKeyClass(Text.class);
	job.setOutputValueClass(Text.class);

	FileInputFormat.addInputPath(job, new Path("/input"));
	FileOutputFormat.setOutputPath(job, new Path("/tmp/output"));

	System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}



