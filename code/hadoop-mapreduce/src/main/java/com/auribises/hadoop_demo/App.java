package com.ahampriyanshu.hadoop_demo;

import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;


public class App extends Configured implements Tool{
	
    public static void main( String[] args ) throws Exception {
        System.out.println( "Reviews Analysis" );
        
        // Let the main function execute the run method for Hadoop Job in the background
        int code = ToolRunner.run(new App(), args);
        System.exit(code); // terminate the program
        
    }

	public int run(String[] args) throws Exception {

		
		// Create a Hadoop Job
		Job job = new Job();
		
		// Set the Class
		job.setJarByClass(App.class);
		
		// Set the name
		job.setJobName("ReviewsJob");
		
		// Provide Input File and Output Directory Path
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		// Set Classes for Key Value Pair
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		job.setOutputFormatClass(TextOutputFormat.class);
		
		// Set Mapper Class
		job.setMapperClass(MyMapper.class);
		
		// Set Reducer Class
		job.setReducerClass(MyReducer.class);
		
		// Execute the Job
		int completionValue = job.waitForCompletion(true) ? 0 : 1;
		
		// Show the Message
		if(job.isSuccessful()) {
			System.out.println("Reviews Job Finished");
		}else {
			System.out.println("Reviews Job Failed");
		}
		
		return completionValue;
	}
    
}
