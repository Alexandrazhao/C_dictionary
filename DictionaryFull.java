import java.util.HashMap;  
import java.util.Scanner;
import java.util.*;
import java.io.*;
import java.io.File;


public class DictionaryFull{
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
		Scanner splitted = input.useDelimiter(" |\\n");
		while (/*splitted.hasNext() &&*/ n < 10){
			dictionary.put(splitted.next(), splitted.next());
			n = n + 1;
		} 
		System.out.println(Arrays.asList(dictionary));
		input.close();
	}
}
