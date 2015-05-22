package de.freegroup.util.file;


import java.io.*;
import java.util.*;
/**
 * Title:        short-i
 * Description:  Information retrival System with human language interface
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author
 * @version 1.0
 */

public class Directory
{
    public static ArrayList getAll(File folder, boolean recursive)
    {
        ArrayList list = new ArrayList();
        File[] files = folder.listFiles();
        for(int i=0; i<files.length; i++)
        {
            if(files[i].isDirectory())
            {
                if(recursive)
                {
                    list.addAll(getAll(files[i], recursive));
                }
            }
            else
            {
                list.add(files[i]);
            }
        }
        return list;
    }

    public static ArrayList getAllDirs(File folder, boolean recursive)
    {
        ArrayList list = new ArrayList();
        File[] files = folder.listFiles();
        for(int i=0; i<files.length; i++)
        {
            if(files[i].isDirectory())
            {
                list.add(files[i]);
                if(recursive)
                    list.addAll(getAllDirs(files[i], recursive));
            }
        }
        return list;
    }

    public static void main(String[] params)
    {
        File temp = new File("C:\\Temp");
        ArrayList list = Directory.getAll(temp, true);
        Iterator it = list.iterator();
        while(it.hasNext())
        {
            System.out.println(((File)(it.next())).getAbsolutePath());
        }
        System.out.println( "Number of Files: " +  list.size());
    }
}