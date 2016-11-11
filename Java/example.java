
import java.nio.file.*;

import com.github.dlaperriere.*;

public class example {

    static {
        Path current_path = Paths.get("");
        String cwd = current_path.toAbsolutePath().toString();
        System.setProperty("java.library.path", cwd);
        System.err.println("current path is :" +cwd);

	//test load swig/java Fastareader dll    
        System.loadLibrary("FastaReader");
    }

    public static void main(String argv[]) {
        System.out.println(" * creating FastaReader");
        FastaReader fr = new FastaReader("t.fa");

        System.out.println(" * reading sequences");
        while (fr.hasNextSequence()) {
            fr.readSequence();
            long slength = fr.SequenceLength();

            System.out.println( "\tsequence "+fr.Id()+" : \t"+fr.Description()+" \t"+slength+"\t"+fr.Sequence() );


        } 
    } 

}
