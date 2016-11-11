package com.github.dlaperriere;

import java.nio.file.*;
import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import gnu.getopt.Getopt;
import com.github.dlaperriere.*;


/**
 *  FastaTools command line
 */
public class FastaTools {

    private static final Logger logger = LoggerFactory.getLogger(FastaTools.class);

    public static void  usage() {
        System.out.println("");
        System.out.println(" FastaTools  -c command   \n");
        System.out.println(" head:   Print the first n sequences of a fasta file   ");
        System.out.println(" java -jar FastaTools-all-1.0.jar -c head -f file.fa -n 2     \n");
        System.out.println(" stats:  Sequence stats  ");
        System.out.println(" java -jar FastaTools-all-1.0.jar -c stats -f file.fa     ");
    }

    /**
     * Parse command line arguments
     */
    private  static FastaToolsOptions parseArgs(String[] args) {
        Getopt g = new Getopt("FastaTools", args, "c:f:n:h");
        //
        int c;
        String arg;
        FastaToolsOptions faoptions = new FastaToolsOptions();
        while ((c = g.getopt()) != -1)
        {
            switch(c)
            {
            case 'h':
                usage();
                System.exit(0);
                break;
            case 'c':
                arg = g.getOptarg();
                // System.out.print("c: " + (char)c + " with an argument of " + ((arg != null) ? arg : "null") + "\n");
                faoptions.command = arg;
                break;
            //
            case 'f':
                arg = g.getOptarg();
                // System.out.print("f: " + (char)c + " with an argument of " + ((arg != null) ? arg : "null") + "\n");
                faoptions.fasta_file = arg;
                break;
            //
            case 'n':
                arg = g.getOptarg();
                // System.out.print("g: " + (char)c + " with an argument of " + ((arg != null) ? arg : "null") + "\n");
                faoptions.n = Integer.parseInt(arg);
                break;
            //
            case '?':
                break; // getopt() already printed an error
            //
            default:
                System.out.print("getopt() returned " + c + "\n");
            }


        }
        return faoptions;
    }

    /*
     *  Main: parse command line & run command
     */
    public static void main(String[] args) {

        Path current_path = Paths.get("");
        String cwd = current_path.toAbsolutePath().toString();
        System.setProperty("java.library.path", cwd);

        int status = 0;
        logger.debug("[MAIN] start at : {}", getCurrentDate());
        logger.debug("[MAIN] current path is: {}", cwd);
        FastaToolsOptions options = parseArgs(args);



        if (options.command.equals("head")) {
            if(!Files.exists(Paths.get(options.fasta_file))) {
                System.out.print(" invalid file \""+options.fasta_file+"\" as -f parameter, cannot continue...");
                System.exit(-1);
            }
            FastaHead.head(options.fasta_file, options.n);
        }
        else if(options.command.equals("stats")) {
            if(!Files.exists(Paths.get(options.fasta_file))) {
                System.out.print(" invalid file \""+options.fasta_file+"\" as -f parameter, cannot continue...");
                System.exit(-1);
            }
            FastaStats.stats(options.fasta_file);
        }
        else {
            System.out.print("unknown command \""+options.command+"\"");
            usage();
            //status = -1;
        }

        logger.debug("[MAIN] end at : {}", getCurrentDate());
        System.exit(status);
    }

    /*
     * Utility method for logging
     */
    private static Date getCurrentDate() {
        return new Date();
    }

}
