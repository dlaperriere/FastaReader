
import java.nio.file.*;

import org.junit.Test;
import static org.junit.Assert.*;
import static junit.framework.TestCase.fail;

import com.github.dlaperriere.*;

/*
 * Test FastaReader
 *
 * @author David Laperriere
 */
public  class FastaReaderTest {

    public FastaReaderTest() {}

    //test load swig/java Fastareader dll
    @Test public  void test_FastaReader_load_dll() {

        boolean ok = false;
        try {
            System.loadLibrary("FastaReader");
            ok = true;
        } catch (UnsatisfiedLinkError ue) {
        }
        catch (Exception e) {
        }

        assertTrue(ok);
    }


    // test fasta file t.fa
    @Test public void test_FastaReader_fasta() {

        		

        //FastaReaderProject/Java
	    Path current_path = Paths.get("");
                String cwd = current_path.toAbsolutePath().toString();
                 System.setProperty("java.library.path", cwd);
        System.err.println("current path is :" +cwd);
  
        try {
            System.loadLibrary("FastaReader");
            String test_file = "t.fa";
            FastaReader fr = new FastaReader(test_file);


            while (fr.hasNextSequence()) {
                fr.readSequence();
                long slength = fr.SequenceLength();

                System.out.println( test_file+"\tsequence "+fr.Id()+" : \t"+fr.Description()+" \t"+slength+"\t"+fr.Sequence() );
                if(fr.Id().equals("4")) {
                    long expected_size = 15;
                    String expected_seq = "AcgtNn*--TGCaxX";
                    assertTrue(fr.Sequence() .equals(expected_seq));
                    assertTrue( expected_size == slength );

                }
                else {
                    assertTrue(!fr.Id().equals("4"));
                }

                assertTrue( slength >= 0 );

            }

        } catch (UnsatisfiedLinkError e) {

            System.out.println("Failed to load FastaReader :"+e);
        }
        catch (Exception e) {
            System.out.println("FastaReader failed :"+e);
        }

    }
    

    /**
      * Main
      */
    public static void main(String argv[]) {

        try {
            System.loadLibrary("FastaReader");
            System.out.println("Loaded FastaReader");
        } catch (UnsatisfiedLinkError e) {

            System.out.println("Failed to load FastaReader :"+e);
        }

    }
}
