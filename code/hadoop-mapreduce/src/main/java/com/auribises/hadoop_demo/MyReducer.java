package com.ahampriyanshu.hadoop_demo;

import java.io.IOException;
import java.util.Iterator;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class MyReducer extends Reducer<Text, IntWritable, Text, IntWritable>{

	@Override
	protected void reduce(Text key, Iterable<IntWritable> values,
			Reducer<Text, IntWritable, Text, IntWritable>.Context context) throws IOException, InterruptedException {
		
		// create an initial count variable for the word
		int count = 0;
		// Iterate in the words
		Iterator<IntWritable> iterator = values.iterator();
		
		while(iterator.hasNext()) {
			// keep on adding the value
			count += iterator.next().get();
		}
		
		
		// Write in File (we will mention file in -> main function)
		context.write(key, new IntWritable(count));
	}
	
}
