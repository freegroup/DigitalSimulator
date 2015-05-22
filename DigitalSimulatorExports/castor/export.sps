<?xml version="1.0" encoding="UTF-8"?>
<structure version="2" schemafile="export.xsd" workingxmlfile="circuit.xml" templatexmlfile="">
	<nspair prefix="xs" uri="http://www.w3.org/2001/XMLSchema"/>
	<template>
		<match overwrittenxslmatch="/"/>
		<children>
			<xpath allchildren="1"/>
		</children>
	</template>
	<pagelayout>
		<properties pagemultiplepages="0" pagenumberingformat="1" pagenumberingstartat="1" paperheight="11in" papermarginbottom="0.79in" papermarginleft="0.6in" papermarginright="0.6in" papermargintop="0.79in" paperwidth="8.5in"/>
		<coverpage>
			<template>
				<match overwrittenxslmatch="/"/>
				<children>
					<table>
						<properties align="center" width="80%"/>
						<children>
							<tablebody>
								<children>
									<tablerow>
										<children>
											<tablecol>
												<properties rowspan="2" width="20"/>
											</tablecol>
											<tablecol>
												<properties height="50"/>
											</tablecol>
										</children>
									</tablerow>
									<tablerow>
										<children>
											<tablecol>
												<children>
													<paragraph paragraphtag="fieldset">
														<children>
															<paragraph paragraphtag="center">
																<children>
																	<paragraph paragraphtag="h1">
																		<children>
																			<newline/>
																			<text fixtext="DigitalSimulator"/>
																			<newline/>
																			<newline/>
																		</children>
																	</paragraph>
																	<paragraph paragraphtag="h2">
																		<children>
																			<text fixtext="Author"/>
																			<template>
																				<match match="circuit"/>
																				<children>
																					<template>
																						<match match="objects"/>
																						<children>
																							<template>
																								<match match="documenttation"/>
																								<children>
																									<template>
																										<match match="DocumentDocumentation"/>
																										<children>
																											<template>
																												<match match="version"/>
																												<children>
																													<template>
																														<match match="v_01x00"/>
																														<children>
																															<template>
																																<match match="author"/>
																																<children>
																																	<template>
																																		<match match="firstName"/>
																																		<children>
																																			<paragraph paragraphtag="p">
																																				<children>
																																					<xpath allchildren="1"/>
																																				</children>
																																			</paragraph>
																																		</children>
																																	</template>
																																</children>
																															</template>
																														</children>
																													</template>
																												</children>
																											</template>
																										</children>
																									</template>
																								</children>
																							</template>
																						</children>
																					</template>
																				</children>
																			</template>
																			<newline/>
																			<newline/>
																			<newline/>
																		</children>
																	</paragraph>
																</children>
															</paragraph>
														</children>
													</paragraph>
												</children>
											</tablecol>
										</children>
									</tablerow>
								</children>
							</tablebody>
						</children>
					</table>
				</children>
			</template>
		</coverpage>
	</pagelayout>
</structure>
