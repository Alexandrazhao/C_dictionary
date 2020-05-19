import java.util.*;
import java.io.*;
import java.lang.Object;
import java.io.File; 
import java.util.Scanner; 

public class LinkedList {
	private Node first; // top of stack - most recently added node
	static int n; // number of nodes

	private static class Node {
		String key;
		String value;
		Node next;
	}

	public Node createNode(String key, String value) {
		Node oldfirst = first;
		first = new Node();
		first.key = key;
		first.value = value;
		first.next = oldfirst;
		n = n + 1;
		return first;
	}
	
	public int size() {
		return n;
	}

	public static void printNode(Node node) {
		System.out.print("Node is: " + node.key + " " + node.value + "\n");
	}
   
	private static void searchForNode(Node node, Stack<Node> stack) {
		for (int i = 0; i < stack.size(); i++) {
			Node node1 = stack.get(i);
			if (node1.key == node.key && node1.value == node.value) {
				System.out.println("Node found: ");
				printNode(node1);
			} else {
				continue;

			}
		}

	}
   
	private static int searchForKey(String key, Stack<Node> stack) {
		for (int i = 1; i < stack.size(); i++) {
			Node node1 = stack.pop();
			searchForNode(node1, stack);
			//System.out.println(node1.key);
			if (node1.key.equals(key)) {
				//System.out.println("The key I am looking for is"+ key);
				//System.out.println("Node found"+key);
				//printNode(node1);
				return 1;
				//break;
			} else {
				//System.out.println("Hi, I'm in continue");
				continue;
			}
		}
		return 0;
	}
   
	public static void print(Stack<Node> stack) {
		int i = 0;
		while(i < stack.size()) {
			System.out.println(stack.peek().key + " " + stack.peek().value);
			stack.pop();
			i = i + 1;
			//System.out.println("i = " + i);
		}
	}

	public static void main(String args[]) throws FileNotFoundException {
		//System.out.print("I'm in main\n");
		long startTime = System.nanoTime();
		Stack<Node> dictionary = new Stack<Node>();
		LinkedList dict = new LinkedList();
		File file = new File("macbeth-processed.txt");
		Scanner input = new Scanner(file);
		int m = 0; // number of words in dictionary
		while (input.hasNext()) {
			String line = input.nextLine();
			String[] splitted = line.split(" ");
			// System.out.println(splitted[0] + ":" + splitted[1]);
			// System.out.println("Splitted length:" + splitted.length);
			//int init_count = 0;
			for (int i = 0; i < splitted.length; i++) {
				// System.out.println("i is:" + i);
				// System.out.println("splitted[i] is:" + splitted[i]);
				Node nowa = dict.createNode(splitted[i], null);
				// printNode(nowa);
				dictionary.push(nowa);
				//print(dictionary);
				//int index = dictionary.search(splitted[i]);
				//dict.get(1);
				//searchForNode(nowa, dictionary);
            	//searchForKey("macbeth", dictionary);
				//System.out.println("index = " + index);
				// System.out.println("The element is: " + dictionary.get(index));
				// String b = dictionary.get(splitted[i]);
				// System.out.println(splitted[i] + " " + b);
				m = m + 1;
			}
			Arrays.fill(splitted, null);
			
			//print(dictionary);
			//System.out.println("m= " + m);
			//searchForNode("project", dictionary);
			/*Node test = new Node();
			test.key = "you";
			test.value = null;
			searchForNode(test, dictionary);*/
		}
		input.close();
		long endTime = System.nanoTime();
		long timeElapsed = endTime - startTime;
		System.out.println("Time elasped of put in miliseconds: " + (timeElapsed)/1000000);
		System.out.println("Average time of put per argument in nanoseconds: " + timeElapsed/m);
      	//String[] to_get = {"macbeth", "duncan"};
		
      /*
      for (int i = 0; i<to_get.length; i++){
         System.out.println("Get(" + to_get[i] + "): " + dict.get(to_get[i]));
         //System.out.println("We get "+ to_get[i] + dict.get(to_get[i]));
      }
      */
      //dict.getFirst("Hello");

		//searchForKey("macbeth", dictionary);
		//System.out.println(searchForKey("macbeth", dictionary));
		long startTime2 = System.nanoTime();
		Scanner input2 = new Scanner(file);
		int init_count = 0;
		while (input2.hasNext()) {
			String line = input2.nextLine();
			String[] splitted = line.split(" ");
			for (int i = 0; i < splitted.length; i++) {
	
				Node nowa = dict.createNode(splitted[i], null);
				// printNode(nowa);
				dictionary.push(nowa);
				if(searchForKey("macbeth", dictionary) == 1){
						init_count = init_count + 1;
				}
				//searchForKey("macbeth", dictionary);
				//System.out.println(searchForKey("macbeth", dictionary));

				m = m + 1;
		  	}
			Arrays.fill(splitted, null);
		} 
		input2.close();
		long endTime2 = System.nanoTime();
		long timeElapsed2 = endTime2 - startTime2;
		System.out.println("# 2 Time elasped for finding macbeth in miliseconds: " + (timeElapsed)/1000000);
		//System.out.println("Average time of put per argument in nanoseconds: " + timeElapsed/m);
		System.out.println("We have found "+init_count + " macbeth");
	}

}


