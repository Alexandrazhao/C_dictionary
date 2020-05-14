import java.util.HashMap; 
import java.util.Map; 
import java.util.Scanner;
import java.lang.Object;
import java.util.*;
import java.io.*;
import java.io.File;
//import edu.princeton.cs.algs4.*;
import java.io.FileReader;

public class DictionaryNull{
	public static void main(String args[]) throws FileNotFoundException{
		HashMap<String, String> dictionary = new HashMap<>();
		/*dictionary.put("hello", "world");    --- test for dictionary
		if (dictionary.containsKey("hello")) { 
			String a = dictionary.get("hello"); 
			System.out.println("value for key" + " \"hello\" is:- " + a); 
			} */
		File file = new File("input.txt");
		Scanner input = new Scanner(file);
		int n = 0; //number of words in dictionary
		while (input.hasNext() && n < 5){
			String line = input.nextLine();
			String[] splitted = line.split(" ");
			//System.out.println(splitted[0] + ":" + splitted[1]);
			//System.out.println("Splitted length:" + splitted.length);
			for(int i = 0; i < splitted.length; i++){
				//System.out.println("i is:" + i);
				//System.out.println("splitted[i] is:" + splitted[i]);
				dictionary.put(splitted[i], null);
				String b = dictionary.get(splitted[i]);
				System.out.println(splitted[i] + " " + b);
			}
			Arrays.fill(splitted, null);
			n = n + 1;
		}
	}
}