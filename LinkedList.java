import java.util.*;
import java.io.*;
import java.lang.Object;

public class LinkedList {
    private static Node first; // top of stack - most recently added node
    private int n; //number of nodes
    private static class Node {
        String key;
        String value;
        Node next;
    }
    
     public static Node createNode(String key, String value) {
    	Node oldfirst = first;
    	first = new Node();
    	first.key = key;
    	first.value = value;
    	return first;
    }
    public static void main(String args[]) throws FileNotFoundException{
        System.out.print("I'm in main");
        Stack<Node> dictionary = new Stack<Node>();
        File file = new File("test.txt");
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
				Node nowa = createNode(splitted[0], null);
				dictionary.push(nowa);
				//String b = dictionary.get(splitted[i]);
				//System.out.println(splitted[i] + " " + b);
			}
			Arrays.fill(splitted, null);
			n = n + 1;
		}
		input.close();
	}
}
