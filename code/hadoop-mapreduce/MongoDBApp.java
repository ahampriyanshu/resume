package com.ahampriyanshu.cms;


import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

import org.bson.Document;
import org.bson.types.ObjectId;

import com.mongodb.ConnectionString;
import com.mongodb.MongoClientSettings;
import com.mongodb.ServerApi;
import com.mongodb.ServerApiVersion;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;


public class App {
	
	
    public static void main( String[] args ){
    	
        System.out.println( "MongoDB App" );
        

		ConnectionString connectionString = new ConnectionString("");
		MongoClientSettings settings = MongoClientSettings.builder()
		        .applyConnectionString(connectionString)
		        .serverApi(ServerApi.builder()
		            .version(ServerApiVersion.V1)
		            .build())
		        .build();
		MongoClient mongoClient = MongoClients.create(settings);
		MongoDatabase database = mongoClient.getDatabase("auridb");
		MongoCollection<Document> collection = database.getCollection("students");
		
		// Print the DataBase Name
		System.out.println("DB Name: "+database.getName());
		
		
		/*// Fetch All the DataBases from MongoDB and print there information as JSON
		List<Document> docs = mongoClient.listDatabases().into(new ArrayList());
		// Using forEach Loop and Lambda Expression => Java8 Feature
		docs.forEach(db -> System.out.println(db.toJson()));
		*/
		
		Scanner scanner = new Scanner(System.in);
		
		while(true) {
			
			System.out.println("1. To Add Student");
			System.out.println("2. To Update Student");
			System.out.println("3. To Delete Student");
			System.out.println("4. To Fetch All Students");
			System.out.println("5. To Fetch Student with Roll Number");
			System.out.println("6. To Quit");
			
			System.out.println("Enter Your Choice: ");
			int choice = scanner.nextInt();
			System.out.println();
			
			if(choice == 6) {
				break;
			}
			
			if(choice == 1) {
				Document document = new Document("_id", new ObjectId());
				
				scanner.nextLine();
				
				System.out.println("Enter Name: ");
				String name = scanner.nextLine();
				
				System.out.println("Enter RollNumber: ");
				int roll = scanner.nextInt();
				
				System.out.println("Enter Age: ");
				int age = scanner.nextInt();
				
				document.append("name", name);
				document.append("rollNumber", roll);
				document.append("age", age);
				document.append("createdOn", new Date());
				
				collection.insertOne(document);
				System.out.println(name+" Added to DataBase :)");
				
				
			}
			
		}
        
    }
}
