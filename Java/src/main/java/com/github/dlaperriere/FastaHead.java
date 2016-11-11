package com.github.dlaperriere;

/**
 * FastaTools head command
 */
public class FastaHead {

    public static void head(String fasta_file , int n)  {
        try {
            System.err.println("# Head   "+fasta_file+" "+n);

            System.loadLibrary("FastaReader");

            FastaReader fr = new FastaReader(fasta_file);

            int sequence_count = 0;
            while (fr.hasNextSequence()) {
                sequence_count++;
                fr.readSequence();

                if(sequence_count <= n) {
                    long slength = fr.SequenceLength();
                    System.out.println( ">"+fr.Id()+"  "+fr.Description()+" \n"+fr.Sequence() );

                }


            }

        } catch (UnsatisfiedLinkError e) {

            System.out.println("Failed to load FastaReader :"+e);
        }
        catch (NullPointerException e) {
            System.out.println("FastaReader failed :"+e);
        }
        catch (Exception e) {
            System.out.println("FastaReader failed :"+e);
        }
    }

}