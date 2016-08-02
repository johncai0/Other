
package demo;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class demo {

    public static class demoMapper extends Mapper<Object, Text, Text, Text> {

	public void map(Object key, Text value, Context context) throws IOException, InterruptedException {

	    String[] arr = value.toString().split(String.valueOf((char)(22)));
	    if (!(arr.length == 27 || arr.length == 28 || arr.length == 11))
		System.out.println(arr.length);

	    //System.out.println("map::" + value);
	    /*
	       log_time = 		value[0]
	       place_id = 		value[1]
	       creative_id = 		value[2]
	       group_id = 		value[3]
	       campaign_id = 		value[4]
	       account_id = 		value[5]
	       bidding = 		value[6]
	       target = 		value[7]
	       setting_region = 	value[8]
	       url = 			value[9]
	       refer = 		value[10]
	       keyword = 		value[11]
	       show_id = 		value[12]
	       cookie = 		value[13]
	       ip = 			value[14]
	       ip_region = 		value[15]
	       url_region = 		value[16]
	       department = 		value[17]
	       user_agent = 		value[18]
	       time = 			value[19]
	       state = 		value[20]
	       style = 		value[21]
	       title = 		value[22]
	       mk = 			value[23]
	       display_style = 	value[24]
	       bidding_model = 	value[25]
	       device = 		value[26]
	       */
	}
    }

    public static class demoReducer extends Reducer<Text, Text, Text, Text> {

	public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {

	    for (Text value : values) {

		System.out.println("reduce::" + key.toString() + "::" + value.toString());
		// context.write(key, Text.get());
	    }
	}
    }

    public static void main(String[] args) throws Exception {

	Configuration conf = new Configuration();
	Job job = Job.getInstance(conf);
	job.setJarByClass(demo.class);

	job.setMapperClass(demoMapper.class);
	// job.setReducerClass(demoReducer.class);

	job.setOutputKeyClass(Text.class);
	job.setOutputValueClass(Text.class);

	FileInputFormat.addInputPath(job, new Path("/data/*"));
	FileOutputFormat.setOutputPath(job, new Path("/tmp/output"));

	System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}



