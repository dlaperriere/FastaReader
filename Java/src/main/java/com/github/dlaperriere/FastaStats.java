package com.github.dlaperriere;

import java.util.regex.*;
import java.util.StringJoiner;

/**
 * FastaTools stats command
 */
public class FastaStats {

    public static void stats(String fasta_file)  {


        try {
            System.out.println("# Stats   "+fasta_file);

            System.loadLibrary("FastaReader");

            FastaReader fr = new FastaReader(fasta_file);
            String header = String.join("\t","seq_id", "seq_num", "length bp",
                                        "unmasked bp", "masked bp", "% masked");
            System.out.println(header);
            int sequence_count = 0;
            while (fr.hasNextSequence()) {
                sequence_count++;
                fr.readSequence();


                String unmasked = fr.Sequence();
                String masked = unmasked.replaceAll("[A-Z\\-\\*]","");
                //System.out.println(unmasked+" <--> "+masked);
                int percent = 0;
                if(unmasked.length() > 0) {
                    percent = 100*(masked.length())/unmasked.length();
                }
                String stats = String.join("\t",fr.Id(),  "r"+String.valueOf(sequence_count),  String.valueOf(unmasked.length()),
                                           String.valueOf(unmasked.length()-masked.length()),  String.valueOf(masked.length()),  String.valueOf(percent));
                System.out.println(stats);
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