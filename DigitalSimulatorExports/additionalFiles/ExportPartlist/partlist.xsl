<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE stylesheet [
	<!ENTITY st0 "stroke:#000000;stroke-width:0.25;fill:none">
	<!ENTITY stt0 "fill:#000000;font-family:Arial;font-size:5">
]>
<?xmlspysamplexml D:\FreeGroup\DigitalSimulatorExports\additionalFiles\ExportPartlistPDF\partlist.xml?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
	<!-- The main template. Processing starts here -->
	<xsl:template match="/circuit">
		<fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format">
			<!--
		       Dimension und Reihenfolge der einzelnen Seiten festlegen 
		    -->
			<fo:layout-master-set>
				<!-- Seitenbeschreibung des Deckblattes -->
				<fo:simple-page-master master-name="deckblatt" page-height="29.7cm" page-width="21cm" margin-top="1cm" margin-bottom="1cm" margin-left="2.5cm" margin-right="2.5cm">
					<fo:region-before extent="6cm"/>
					<fo:region-body margin-top="15cm" margin-bottom="1.5cm" padding="5mm"/>
				</fo:simple-page-master>
				<!-- Seitenbeschreibung des eigentlichen Inhaltes -->
				<fo:simple-page-master master-name="inhalt" page-height="29.7cm" page-width="21cm" margin-top="1cm" margin-bottom="1cm" margin-left="2.5cm" margin-right="2.5cm">
					<fo:region-body margin-top="1cm" margin-bottom="1.5cm" padding="5mm"/>
					<fo:region-before extent="3cm"/>
					<fo:region-after extent="0.5cm"/>
				</fo:simple-page-master>
			</fo:layout-master-set>
			<!--
				Inhalt des Deckblattes definieren 
			-->
			<fo:page-sequence master-reference="deckblatt">
				<fo:static-content flow-name="xsl-region-before">
					<fo:block border-bottom-width="0.3pt" border-bottom-style="solid" text-align="center" font-size="20pt" font-family="sans-serif">
						 Schaltungsaufbau mit dem DigitalSimulator
					</fo:block>
				</fo:static-content>
				<fo:flow flow-name="xsl-region-body">
					<fo:block text-align="left" space-after.optimum="25pt">
						<fo:external-graphic src="plugins/ExportPartlistPDF/TITELBILD.gif"/>
					</fo:block>
					<fo:block text-align="left" font-size="10pt" font-family="sans-serif">
						<xsl:text>Aufbau von realen Schaltung mit den Simulationsdaten des DigitalSimulators.</xsl:text>
					</fo:block>
					<fo:block text-align="left" font-size="10pt" font-family="sans-serif">
						<xsl:text>Copyright &#169; by Andreas Herz</xsl:text>
					</fo:block>
					<fo:block text-align="left" font-size="10pt" font-family="sans-serif">
						<xsl:text>www.FreeGroup.de</xsl:text>
					</fo:block>
				</fo:flow>
			</fo:page-sequence>
			<!--
				Inhalt der Schaltungsbeschreibung definieren 
			-->
			<fo:page-sequence master-reference="inhalt">
				<!--
					print the header of the page
				-->
				<fo:static-content flow-name="xsl-region-before">
					<fo:block text-align="center" font-size="8pt" font-family="sans-serif" line-height="5pt">
						[ www.DigitalSimulator.de ]
					</fo:block>
				</fo:static-content>
				<!--
					print the footer of the page
				-->
				<fo:static-content background-color="black" flow-name="xsl-region-after">
					<fo:table space-after.optimum="15pt">
						<fo:table-column column-width="10%"/>
						<fo:table-column column-width="80%"/>
						<fo:table-column column-width="10%"/>
						<fo:table-body font-size="10pt" font-family="sans-serif">
							<fo:table-row line-height="12pt">
								<fo:table-cell>
										</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="center">
										<xsl:value-of select="/circuit/@name"/>
									</fo:block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="end" font-size="10pt" font-family="sans-serif" line-height="10pt">
												Seite <fo:page-number/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
						</fo:table-body>
					</fo:table>
				</fo:static-content>
				<!-- 
					print the content itself
				-->
				<fo:flow flow-name="xsl-region-body">
					<fo:block>
						<fo:block background-color="#EEEEEE" font-size="14pt" text-align="center" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>Schaltung</xsl:text>
							<xsl:text disable-output-escaping="yes"> [</xsl:text>
							<xsl:value-of select="@name"/>
							<xsl:text>]</xsl:text>
						</fo:block>
						<!--
						    EINLEITUNG
						-->
						<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>
							          Dieses PDF-Dokument wurde mit dem DigitalSimulator [www.digital-simulator.de] aus einer normalen Simulationsdatei generiert. 
						    </xsl:text>
						</fo:block>
						<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>
							         Mit dieser Anleitung ist man nun in der Lage die unten schematisch dargestelle Schaltung mit realen Bauteilen der Digitaltechnik 
							         nachzubauen und auszutesten. Dies stellt die perfekte Ergänzung zur grauen Theorie dar. 
						    </xsl:text>
						</fo:block>
						<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>
							          Es wurde versucht nur Standartbauteile zu verwenden. Alle Schalter oder Taster in der Schaltung werden durch 2 NAND Gatter 
							          entprellt (siehe dazu mehr in [Grundlagen.pdf] des DigitalSimulators). 
						    </xsl:text>
						</fo:block>
						<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>
							         Zum Aufbau der Schaltung sind keine Lötarbeiten oder das Herstellen von Platinen notwendig. Die Anleitung ist dafür ausgelegt 
							         die Schaltung auf einem Steckbrett nachzubauen.
						    </xsl:text>
						</fo:block>
						<fo:block font-size="12pt" text-align="center" font-family="sans-serif" space-after.optimum="5pt">
							<xsl:text>
							          Ich wünschen Ihnen viel Spaß beim Nachbau der Schaltung!
						    </xsl:text>
						</fo:block>
						<!-- 
					      Bild der Schaltung aus dem DigitalSimulator
					    -->
						<fo:block font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
							<xsl:text>Digital Schaltplan</xsl:text>
						</fo:block>
						<fo:block text-align="center">
							<fo:external-graphic src="url('file:///{//imagePath}')"/>
						</fo:block>
						<!--
						    SCHALTUNGSAUFBAU
 					    -->
						<fo:block font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
							<xsl:text>Schaltungsaufbau</xsl:text>
						</fo:block>
						<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
							<fo:list-block>
								<fo:list-item>
									<!-- insert a bullet -->
									<fo:list-item-label end-indent="label-end()">
										<fo:block>
											<fo:inline font-family="Courier">o</fo:inline>
										</fo:block>
									</fo:list-item-label>
									<!-- list text -->
									<fo:list-item-body start-indent="body-start()">
										<fo:block text-align="start">
											<xsl:text>Stecken Sie alle Bauteile in der angegebenen Reihenfolge auf das Steckbrett.</xsl:text>
										</fo:block>
									</fo:list-item-body>
								</fo:list-item>
								<fo:list-item>
									<!-- insert a bullet -->
									<fo:list-item-label end-indent="label-end()">
										<fo:block>
											<fo:inline font-family="Courier">o</fo:inline>
										</fo:block>
									</fo:list-item-label>
									<!-- list text -->
									<fo:list-item-body start-indent="body-start()">
										<fo:block text-align="start">
											<xsl:text>Verbinden Sie die Pins der Bauteile wie in der Liste angegeben mit den Steckverbindungen (Kabeln).</xsl:text>
										</fo:block>
									</fo:list-item-body>
								</fo:list-item>
								<fo:list-item>
									<!-- insert a bullet -->
									<fo:list-item-label end-indent="label-end()">
										<fo:block>
											<fo:inline font-family="Courier">o</fo:inline>
										</fo:block>
									</fo:list-item-label>
									<!-- list text -->
									<fo:list-item-body start-indent="body-start()">
										<fo:block text-align="start">
											<xsl:text>Achten Sie bei dem Verbinden der Pins unbedingt auf die Pinnummer. Eine Verpoolung der Bauteile ist unbedingt zu vermeiden.</xsl:text>
										</fo:block>
									</fo:list-item-body>
								</fo:list-item>
								<fo:list-item>
									<!-- insert a bullet -->
									<fo:list-item-label end-indent="label-end()">
										<fo:block>
											<fo:inline font-family="Courier">o</fo:inline>
										</fo:block>
									</fo:list-item-label>
									<!-- list text -->
									<fo:list-item-body start-indent="body-start()">
										<fo:block text-align="start">
											<xsl:text>Die 5Volt Spannungsversorgung wird wie ein normales Bauteil behandelt (siehe Bauteilliste).</xsl:text>
										</fo:block>
									</fo:list-item-body>
								</fo:list-item>
							</fo:list-block>
						</fo:block>

						<!--
					      Bauteilliste 
					    -->
						<fo:block font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
							<xsl:text>Bauteilliste für den Aufbau der Schaltung</xsl:text>
						</fo:block>
						<fo:table space-after.optimum="15pt">
							<fo:table-column column-width="1cm"/>
							<fo:table-column column-width="15cm"/>
							<fo:table-body font-size="10pt" font-family="sans-serif">
								<xsl:for-each select="parts/part">
									<fo:table-row line-height="12pt">
										<fo:table-cell>
											<fo:block text-align="start">
												<xsl:value-of select="@partNumber"/>
												<xsl:text disable-output-escaping="yes">) </xsl:text>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell>
											<fo:block text-align="start">
												<xsl:value-of select="@name"/>
												<xsl:text disable-output-escaping="yes"> </xsl:text>
											</fo:block>
										</fo:table-cell>
									</fo:table-row>
								</xsl:for-each>
							</fo:table-body>
						</fo:table>
						<fo:block break-before="page" font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
							<xsl:text>Verbindungen (Kabelbrücken) zwischen den Bauteilen</xsl:text>
						</fo:block>
						<fo:table space-after.optimum="15pt">
							<fo:table-column column-width="1cm" border-color="green"/>
							<fo:table-column column-width="0.5cm"/>
							<fo:table-column column-width="1cm"/>
							<fo:table-column column-width="6cm"/>
							<fo:table-column column-width="1cm"/>
							<fo:table-column column-width="0.5cm"/>
							<fo:table-column column-width="1cm"/>
							<fo:table-column column-width="6cm"/>
							<fo:table-header background-color="lightgrey" line-height="8pt">
								<fo:table-row line-height="12pt">
									<fo:table-cell border-left-width="0.1pt" border-left-style="solid" border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
										<fo:block font-size="5pt" text-align="start">von Bauteil</fo:block>
									</fo:table-cell>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid"/>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
										<fo:block font-size="5pt" text-align="start">/ Pin</fo:block>
									</fo:table-cell>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid"/>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-left-width="0.1pt" border-left-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
										<fo:block font-size="5pt" text-align="end">nach Bauteil</fo:block>
									</fo:table-cell>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid"/>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
										<fo:block font-size="5pt" text-align="start">/ Pin</fo:block>
									</fo:table-cell>
									<fo:table-cell border-top-width="0.1pt" border-top-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid" border-right-width="0.1pt" border-right-style="solid"/>
								</fo:table-row>
							</fo:table-header>
							<fo:table-body font-size="10pt" font-family="sans-serif">
								<xsl:for-each select="connections/connection">
									<fo:table-row line-height="12pt">
										<!--
				                       alter the color of the table rows
				                    -->
										<xsl:attribute name="background-color"><xsl:choose><xsl:when test="position() mod 2 = 0">white</xsl:when><xsl:otherwise>#EEEEEE</xsl:otherwise></xsl:choose></xsl:attribute>
										<fo:table-cell font-size="8pt" border-left-width="0.1pt" border-left-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block text-align="center">
												<xsl:value-of select="@fromPart"/>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell font-size="8pt" border-bottom-width="0.1pt" border-bottom-style="solid"/>
										<fo:table-cell font-size="8pt" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block text-align="start">
												<xsl:value-of select="@fromPin"/>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell font-size="8pt" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block font-size="5pt" text-align="start">
												<xsl:value-of select="@fromPinDesc"/>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell font-size="8pt" border-left-width="0.1pt" border-left-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block text-align="center">
												<xsl:value-of select="@toPart"/>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell font-size="8pt" border-bottom-width="0.1pt" border-bottom-style="solid"/>
										<fo:table-cell font-size="8pt" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block text-align="start">
												<xsl:value-of select="@toPin"/>
											</fo:block>
										</fo:table-cell>
										<fo:table-cell border-right-width="0.1pt" border-right-style="solid" border-bottom-width="0.1pt" border-bottom-style="solid">
											<fo:block font-size="5pt" text-align="start">
												<xsl:value-of select="@toPinDesc"/>
											</fo:block>
										</fo:table-cell>
									</fo:table-row>
								</xsl:for-each>
							</fo:table-body>
						</fo:table>
					</fo:block>
					<fo:block break-before="page" font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
						<xsl:text>Bauteilebeschreibung</xsl:text>
					</fo:block>
					<fo:table>
						<fo:table-column column-width="8cm"/>
						<fo:table-column column-width="7cm"/>
						<fo:table-body font-size="10pt" font-family="sans-serif">
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Leuchtdiode</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Bei einer LED ist ein Beinchen kürzer als das andere.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Das kürzere Beinchen ist die Kathode.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Eine Seite der LED ist abgeflacht. Dies ist die Seite mit dem kurzen Beinchen - die Kathode.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/LED.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Diode</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Der elektrische Strom fliesst in Pfeilrichtung durch (also hier von oben nach unten), in der Gegenrichtung sperrt das Element, schön dargestellt mit dem Querbalken.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Ber Farbring kennzeichnet die Kathode.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/DIODE.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Widerstand</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Die Farbringe des Widerstand kennzeichnen seine Wert.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Er hat keine bevorzugte Einbaurichtung.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/RESISTOR.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Potentiometer (Trimmer)</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Sind einstellbare Widerstände.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Bei dem Kauf der Trimmer unbedingt darauf achten, dass man eine kleine Ausführung bekommt. 'Normale' Trimmer passen NICHT in ein normales Steckbrett!</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/POTI.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Elektrolyt-Kondensator</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Bei einer Elko ist ein Beinchen kürzer als das andere.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Es ist unbedingt auf die Poolung zu achten.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Der kurze oder mit (-) gekennzeichnete Anschluß wird hier mit Pin #1 bezeichnet</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/ELKO.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Kondensator</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Bei Keramik/Folien Kondensatoren gibt es keine Einbaurichtung. Diese kann beliebig gewählt werden</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/KONDENSATOR.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Transistor BC107 (TO8 Gehäuse)</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Bei Transistoren ist unbedingt auf richtige Pinbelegung zu achten.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Transistoren haben eine Typenabhängige Pinbelegung.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>An dem Gehäuse ist ein kleines Metall 'Fähnchen' welches den Emitter (Pin#3) kennzeichnet.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Hier ist ein BC107 in einem TO8 Gehäuse abgebildet.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/BC107.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>TTL-Logikbaustein 7400</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Logik-IC der 74xx Reihe.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Enthält 4 NAND's mit jeweils 2 Eingängen (A,B) und einem Ausgang (Y).</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Oben links ist Pin #1.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Die Nummerrierung der Pins erfolgt gegen den Uhrzeigersinn.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/7400.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>TTL-Logikbaustein 7490</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Logik-IC der 74xx Reihe.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Enthält einen BCD Zähler (0-9).</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Oben links ist Pin #1.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Die Nummerrierung der Pins erfolgt gegen den Uhrzeigersinn.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/7490.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Steckbrett</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Das Steckbrett (Breadboard) ist ideal für Versuchsaubauten.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Die rot hervorgehobene Linie zeige exemplarische die elektrische Verbindungen der einzelnen Löcher.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Die Bauteile müssen mit sanften Druck in die dafür vorgesehen Löcher gedrückt werden.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/BREADBOARD02.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
							<fo:table-row line-height="12pt">
								<fo:table-cell>
									<fo:block text-align="start">
										<xsl:text>Steckkabel</xsl:text>
									</fo:block>
									<fo:list-block font-size="8pt" font-family="sans-serif" space-after.optimum="15pt">
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Wird benötigt um die Bauteile auf dem Steckbrett miteinander zu verbinden.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Habe kleine feste Spitzen an den Enden zum besseren einstechen in das Steckbrett.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
										<fo:list-item>
											<!-- insert a bullet -->
											<fo:list-item-label end-indent="label-end()">
												<fo:block>
													<fo:inline font-family="Courier">-</fo:inline>
												</fo:block>
											</fo:list-item-label>
											<!-- list text -->
											<fo:list-item-body start-indent="body-start()">
												<fo:block text-align="start">
													<xsl:text>Kosten zwar ein bischen Geld, ersparen aber Nerven gegenüber normalen Kabeln.</xsl:text>
												</fo:block>
											</fo:list-item-body>
										</fo:list-item>
									</fo:list-block>
								</fo:table-cell>
								<fo:table-cell>
									<fo:block text-align="start">
										<fo:external-graphic scaling="uniform" src="plugins/ExportPartlistPDF/WIRE.gif"/>
									</fo:block>
								</fo:table-cell>
							</fo:table-row>
						</fo:table-body>
					</fo:table>
					<!--
						HAFTUNGSAUSSCHLUSS
					-->
					<fo:block font-size="15pt" font-family="sans-serif" space-after.optimum="5pt" space-before.optimum="15pt">
						<xsl:text>Haftungsausschluß</xsl:text>
					</fo:block>
					<fo:block font-size="10pt" font-family="sans-serif" space-after.optimum="5pt">
						<xsl:value-of select="description"/>
					</fo:block>
					<fo:block color="#FF0000" font-size="10pt" text-align="center" font-family="sans-serif" space-after.optimum="5pt">
						<xsl:text>Bitte teilen Sie eventuelle Fehler dem Autor dieser Software mit.</xsl:text>
					</fo:block>
				</fo:flow>
			</fo:page-sequence>
		</fo:root>
	</xsl:template>
</xsl:stylesheet>
