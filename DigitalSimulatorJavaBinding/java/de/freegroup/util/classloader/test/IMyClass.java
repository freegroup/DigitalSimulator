/*
 * SAPMarkets Copyright (c) 2001
 * All rights reserved
 *
 * @version $Id: IMyClass.java,v 1.1 2004/01/28 14:33:36 freegroup Exp $
 */

package de.freegroup.util.classloader.test;

/**
 * Base interface for test classes with ident names.
 *
 * @created   11. Juli 2001
 */
public interface IMyClass
{
    /**
     * Get the Version attribute of the IMyClass object.
     *
     * @return               The Version value
     * @exception Exception  Exception raised in failure situation
     */
    public int getVersion()
        throws Exception;
}
