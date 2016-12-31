import java.io.File;
import java.io.PrintWriter;
import java.io.Writer;
import java.util.*;

public class act_main
{

	private static LinkedList<String> cmdlist = new LinkedList<String>();

	public static void main(String[] args)throws Exception {		
			// Parse CommandLine Arguments
			//final Scanner r = new Scanner(new File(args[0]));
			final Scanner r = new Scanner(System.in);
			final Writer w = new PrintWriter(System.out);
			
			cmdlist = read(r);

			System.out.println(cscTranslator.translator(toString(cmdlist)));
	}

	private static Scanner toString(LinkedList<String> output) {
		StringBuilder out = new StringBuilder();
		for(String s : output)
		{
			out.append(s);
			out.append("\n");
		}
		return new Scanner(out.toString());
	}

	private static LinkedList<String> read(Scanner r) {
		LinkedList<String> file = new LinkedList<String>();
		while(r.hasNext())
			file.add(r.nextLine());
		return file;
	}
}
