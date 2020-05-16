import java.util.HashMap;  
import java.util.Scanner;
import java.util.*;
import java.io.*;
import java.io.File;



public class DictionaryFull{
	public static void main(String args[]) throws FileNotFoundException, InterruptedException{
		long startTime = System.nanoTime();
		HashMap<String, String> dictionary = new HashMap<>();
		//TimeUnit.SECONDS.sleep(5);
		/*dictionary.put("hello", "world");    --- test for dictionary
		if (dictionary.containsKey("hello")) { 
			String a = dictionary.get("hello"); 
			System.out.println("value for key" + " \"hello\" is:- " + a); 
		} */
		File file = new File("macbeth-processed.txt");
		Scanner input = new Scanner(file);
		int n = 0; //number of words in dictionary
		Scanner splitted = input.useDelimiter(" |\\n");
		while (splitted.hasNext() /*&& n < 10018*/){
			dictionary.put(splitted.next(), splitted.next());
			//System.out.println("n=" + n);
			//System.out.println("hasNext()=" + splitted.hasNext());
			n = n + 1;
		} 
		//System.out.println(Arrays.asList(dictionary));
		System.out.println("n= " + n);
		input.close();
		long endTime = System.nanoTime();
		long timeElapsed = endTime - startTime;
		System.out.println("Time elasped of put in nanoseconds: " + (timeElapsed));
		System.out.println("Average time of put per argument in nanoseconds: " + timeElapsed/n);
		dictionary.put("apple", "apple");
		dictionary.put("yes", "yes");
		long startTimeGet = System.nanoTime();
		System.out.println("dictionary.get(apple) = " + dictionary.get("apple"));
		System.out.println("dictionary.get(yes) = " + dictionary.get("yes"));
		long endTimeGet = System.nanoTime();
		long timeElapsedGet = endTimeGet - startTimeGet;
		System.out.println("Time elasped of get in nanoseconds: " + timeElapsedGet);
		System.out.println("Average time of get per argument in nanoseconds: " + timeElapsedGet/2);
	}
}
