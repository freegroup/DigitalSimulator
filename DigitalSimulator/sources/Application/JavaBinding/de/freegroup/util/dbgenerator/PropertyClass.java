package de.freegroup.util.dbgenerator;

/**
 * Title:        ShortiDatabase2Java
 * Description:
 * Copyright:    Copyright (c) 2001
 * Company:      short-i
 * @author David Sommer
 * @version 1.0
 */

class PropertyClass
{
    String name;
    String type;
    String description;
    boolean isAutoIncrement;
    boolean isKey;
    boolean unique     = false;
    boolean foreignKey = false;
    String foreignKeyClass;
    String foreignKeyProperty;

    public PropertyClass()
    {
        preInit();
    }

    public PropertyClass(String _name, String _type , boolean _isIdentity)
    {
        preInit();
        name = _name;
        type = _type;
        isAutoIncrement =_isIdentity;
    }

//    public PropertyClass(String name, String type,
//                         String description, boolean isKey,
//                         String foreignKeyClass, String foreignKeyProperty)
//    {
//        preInit();
//        this.name = name;
//        this.type = type;
//        this.description = description;
//        this.isKey = isKey;
//        this.foreignKeyClass = foreignKeyClass;
//        this.foreignKeyProperty = foreignKeyProperty;
//    }

    public void preInit()
    {
        this.name = "";
        this.type = "";
        this.description = "";
        this.isKey = false;
        this.foreignKeyClass = "";
        this.foreignKeyProperty = "";
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public String getName()
    {
        return name;
    }

    public void setIsAutoIncrement(boolean _isAutoIncrement)
    {
        isAutoIncrement = _isAutoIncrement;
    }

    public boolean getIsAutoIncrement()
    {
        return isAutoIncrement;
    }

    public void setType(String type)
    {
        this.type = type;
    }

    public String getType()
    {
        return type;
    }

    public void setDescription(String description)
    {
        this.description = description;
    }


    public String getDescription()
    {
        return description;
    }


    public void setForeignKey(String foreignKeyClass, String foreignKeyProperty)
    {
        this.foreignKeyClass    = foreignKeyClass;
        this.foreignKeyProperty = foreignKeyProperty;
        foreignKey = true;
    }


    public boolean getForeignKey()
    {
        return foreignKey;
    }

    public String getForeignKeyClass()
    {
        return foreignKeyClass;
    }

    public String getForeignKeyProperty()
    {
        return foreignKeyProperty;
    }

    public void setPrimaryKey(boolean isKey)
    {
        this.isKey = isKey;
    }

    public void setUnique(boolean _unique)
    {
        unique = _unique;
    }


    public boolean getPrimaryKey()
    {
        return isKey;
    }

    public boolean getUnique()
    {
        return unique;
    }

}