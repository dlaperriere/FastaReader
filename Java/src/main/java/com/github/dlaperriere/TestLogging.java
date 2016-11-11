package com.github.dlaperriere;

import java.util.Date;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TestLogging {

    private static final Logger logger = LoggerFactory.getLogger(TestLogging.class);

    public static void main(String[] args) {

        logger.debug("[MAIN] start at : {}", getCurrentDate());
        System.out.println("      ...     ");
        logger.debug("[MAIN] end at : {}", getCurrentDate());
    }

    private static Date getCurrentDate() {
        return new Date();
    }

}