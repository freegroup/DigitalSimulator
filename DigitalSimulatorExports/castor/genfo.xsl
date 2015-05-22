<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema">
    <xsl:variable name="fo:layout-master-set">
        <fo:layout-master-set>
            <fo:simple-page-master master-name="cover-page-master" page-height="11in" page-width="8.5in" page-position="first">
                <fo:region-body font-family="Helvetica,Times,Courier" font-size="14pt" />
            </fo:simple-page-master>
            <fo:simple-page-master master-name="default-page" page-height="11in" page-width="8.5in" margin-left="0.6in" margin-right="0.6in">
                <fo:region-body margin-top="0.79in" margin-bottom="0.79in" font-family="Helvetica,Times,Courier" font-size="14pt" />
            </fo:simple-page-master>
        </fo:layout-master-set>
    </xsl:variable>
    <xsl:template match="/">
        <fo:root>
            <xsl:copy-of select="$fo:layout-master-set" />
            <fo:page-sequence master-reference="cover-page-master">
                <fo:flow flow-name="xsl-region-body">
                    <fo:block>
                        <fo:table start-indent="(8.5in - ((8.5in * 80) div 100) ) div 2" end-indent="(8.5in - ((8.5in * 80) div 100) ) div 2" text-align="center" width="80%" space-before.optimum="1pt" space-after.optimum="2pt">
                            <fo:table-column column-width="20pt" />
                            <fo:table-column />
                            <fo:table-body>
                                <fo:table-row>
                                    <fo:table-cell number-rows-spanned="2" width="20pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start" border-style="solid" border-width="1pt" border-color="white">
                                        <fo:block />
                                    </fo:table-cell>
                                    <fo:table-cell height="50pt" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start" border-style="solid" border-width="1pt" border-color="white">
                                        <fo:block />
                                    </fo:table-cell>
                                </fo:table-row>
                                <fo:table-row>
                                    <fo:table-cell padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" display-align="center" text-align="start" border-style="solid" border-width="1pt" border-color="white">
                                        <fo:block>
                                            <fo:block border-style="solid" border-width="1pt" border-color="#808080" padding-start="3pt" padding-end="3pt" padding-before="3pt" padding-after="3pt" space-before.optimum="1pt" space-after.optimum="2pt">
                                                <fo:block>
                                                    <fo:block text-align="center" space-before.optimum="1pt" space-after.optimum="2pt">
                                                        <fo:block>
                                                            <fo:block font-size="24pt" font-weight="bold" space-before.optimum="1pt" space-after.optimum="2pt">
                                                                <fo:block>
                                                                    <fo:block>
                                                                        <fo:leader leader-pattern="space" />
                                                                    </fo:block>DigitalSimulator<fo:block>
                                                                        <fo:leader leader-pattern="space" />
                                                                    </fo:block>
                                                                    <fo:block>
                                                                        <xsl:text>&#xA;</xsl:text>
                                                                    </fo:block>
                                                                </fo:block>
                                                            </fo:block>
                                                            <fo:block font-size="18pt" font-weight="bold" space-before.optimum="1pt" space-after.optimum="2pt">
                                                                <fo:block>Author<xsl:for-each select="circuit">
                                                                        <xsl:for-each select="objects">
                                                                            <xsl:for-each select="documenttation">
                                                                                <xsl:for-each select="DocumentDocumentation">
                                                                                    <xsl:for-each select="version">
                                                                                        <xsl:for-each select="v_01x00">
                                                                                            <xsl:for-each select="author">
                                                                                                <xsl:for-each select="firstName">
                                                                                                    <fo:block space-before.optimum="1pt" space-after.optimum="2pt">
                                                                                                        <fo:block>
                                                                                                            <xsl:apply-templates />
                                                                                                        </fo:block>
                                                                                                    </fo:block>
                                                                                                </xsl:for-each>
                                                                                            </xsl:for-each>
                                                                                        </xsl:for-each>
                                                                                    </xsl:for-each>
                                                                                </xsl:for-each>
                                                                            </xsl:for-each>
                                                                        </xsl:for-each>
                                                                    </xsl:for-each>
                                                                    <fo:block>
                                                                        <fo:leader leader-pattern="space" />
                                                                    </fo:block>
                                                                    <fo:block>
                                                                        <fo:leader leader-pattern="space" />
                                                                    </fo:block>
                                                                    <fo:block>
                                                                        <xsl:text>&#xA;</xsl:text>
                                                                    </fo:block>
                                                                </fo:block>
                                                            </fo:block>
                                                        </fo:block>
                                                    </fo:block>
                                                </fo:block>
                                            </fo:block>
                                        </fo:block>
                                    </fo:table-cell>
                                </fo:table-row>
                            </fo:table-body>
                        </fo:table>
                    </fo:block>
                </fo:flow>
            </fo:page-sequence>
            <fo:page-sequence master-reference="default-page" initial-page-number="1" format="1">
                <fo:flow flow-name="xsl-region-body">
                    <fo:block>
                        <xsl:apply-templates />
                    </fo:block>
                </fo:flow>
            </fo:page-sequence>
        </fo:root>
    </xsl:template>
</xsl:stylesheet>
