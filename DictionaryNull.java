import java.util.HashMap; 
import java.util.Map; 
import java.util.Scanner;
import java.lang.Object;
import java.util.*;
import java.io.*;
import java.io.File;
//import edu.princeton.cs.algs4.*;
import java.io.FileReader;


public class NullDictionary{
	public static void main(String args[]) throws FileNotFoundException{
		long startTime = System.nanoTime();
		HashMap<String, String> dictionary = new HashMap<>();
		/*dictionary.put("hello", "world");    --- test for dictionary
		if (dictionary.containsKey("hello")) { 
			String a = dictionary.get("hello"); 
			System.out.println("value for key" + " \"hello\" is:- " + a); 
			} */
		File file = new File("macbeth-processed.txt");
		Scanner input = new Scanner(file);
		int n = 0;
		while (input.hasNext()){
			String line = input.nextLine();
			String[] splitted = line.split(" ");
			 //number of words in the dictionary
			//System.out.println(splitted[0] + ":" + splitted[1]);
			//System.out.println("Splitted length:" + splitted.length);
			for(int i = 0; i < splitted.length; i++){
				//System.out.println("i is:" + i);
				//System.out.println("splitted[i] is:" + splitted[i]);
				dictionary.put(splitted[i], null);
				//String b = dictionary.get(splitted[i]);
				//System.out.println(splitted[i] + " " + b);
				//System.out.println("Number of words: " + i);
				n = n + 1;
			}
			Arrays.fill(splitted, null);
			
		}
		input.close();
		long endTime = System.nanoTime();
		long timeElapsed = endTime - startTime;
		System.out.println("Time elasped of put in nanoseconds: " + (timeElapsed));
		System.out.println("Average time of put per argument in nanoseconds: " + timeElapsed/n);
		dictionary.put("apple", null);
		dictionary.put("yes", null);
		long startTimeGet = System.nanoTime();
		System.out.println("dictionary.get(apple) = " + dictionary.get("apple"));
		System.out.println("dictionary.get(yes) = " + dictionary.get("yes"));
		long endTimeGet = System.nanoTime();
		long timeElapsedGet = endTimeGet - startTimeGet;
		System.out.println("Time elasped of get in nanoseconds: " + timeElapsedGet);
		System.out.println("Average time of get per argument in nanoseconds: " + timeElapsedGet/2);
		
	}
}
