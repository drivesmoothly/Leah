use XML::LibXML;

# my xml file
my $xmlfile = $ARGV[0];
my $headerfile = $xmlfile . ".h";
my $sourcefile = $xmlfile . ".cpp";

# initialize the parser
my $parser = new XML::LibXML;
# parse the xml file
my $doc = $parser->parse_file( $xmlfile );
my $root = $doc->getDocumentElement;

###############################################################################
# Main
###############################################################################

# generate header declarations
generateDeclarations( $root, $headerfile );
# generate source code
generateSource( $root, $sourcefile );

###############################################################################
# Header file
###############################################################################

# get the nodes list in the order they appear
sub getNodesList {
    my ( $node, $list ) = @_;
    return unless ( $node->nodeType eq &XML_ELEMENT_NODE );
    
    foreach my $child ( $node->getChildnodes ) {
        if ($child->nodeType == XML_ELEMENT_NODE) {
            push @list, $child;
            &getNodesList( $child, $list );
        }
    }
}

# create variables creation from list
sub createVariables {
    my ( $list, $filename ) = @_;
    open HEADER_FILE, ">", $filename or die $!;
    print HEADER_FILE "// This is generated code. DO NOT MODIFY\n";
    print HEADER_FILE "private:\n";
    print HEADER_FILE "\tvoid InitFromXml();\n\n";
    
    foreach my $variable ( @list ) {
        my $attrName;
        eval { $attrName = $variable->getAttributeNode( "Name" )->value; };
        if ( !$@ ) {
            print HEADER_FILE "\t", $variable->nodeName, "* $attrName;\n";
        }
    }
    
    close ( HEADER_FILE );
    print "Variables generated in $filename\n";
}

# generate header declarations
sub generateDeclarations {
    my ( $root, $filename ) = @_;
    my @nodesList;
    getNodesList( $root, \@nodesList );
    createVariables( \@nodesList, $filename );
}

###############################################################################
# Source file
###############################################################################

# generate source code
sub generateSource {
    my ( $root, $filename ) = @_;
    open SOURCE_FILE, ">", $filename or die $!;
    print SOURCE_FILE "// This is generated code. DO NOT MODIFY\n";
    addIncludes( $root->nodeName, SOURCE_FILE );

    # start InitFromXml function
    print SOURCE_FILE "void ", $root->nodeName, "::InitFromXml()\n\t{\n";
    # set properties for parent node
    setPropertiesValues( "this", $root, SOURCE_FILE );
    print SOURCE_FILE "\n";
    # create children and set properties
    foreach my $child ( $root->getChildnodes ) {
        if ( $child->nodeType == XML_ELEMENT_NODE ) {
            createChild( $child, undef, SOURCE_FILE );
        }
    }
    # end InitFromXml function
    print SOURCE_FILE "\t}\n";
    
    close SOURCE_FILE;
    print "Source file generated in $filename.\n";
}

# adds include files to generated source file. includes:
#   controls library (controlslibrary.h)
sub addIncludes {
    my ( $className, $file ) = @_;
    print $file "#include \"controlslibrary.h\"\n";
    print $file "#include \"layoutlibrary.h\"\n";
    print $file "#include \"$className.h\"\n";
    print $file "\n"
}

# creates everything related to a child
#   instantiates a child
#   sets properties values
#   binds properties
#   maps events to handlers
sub createChild {
    my ( $node, $parent, $file ) = @_;
    return unless ( $node and $node->nodeType == &XML_ELEMENT_NODE );

    my $type = $node->nodeName;
    my $name;
    eval { $name = $node->getAttributeNode( "Name" )->value }; return if $@;

    instantiateObject( $type, $name, $file );
    addControl( $name, $parent, $file );
    createControl( $name, $file );
    setPropertiesValues( $name, $node, $file );
    print $file "\n";
    
    foreach my $child ( $node->getChildnodes ) {
        createChild( $child, $name, $file );
    }
}

# instantiates an object
sub instantiateObject {
    my ( $type, $name, $file ) = @_;
    print $file "\t$name = new (ELeave) $type();\n";
}

# sets an object's properties
sub setPropertiesValues {
    my ( $name, $node, $file ) = @_;
    my @attributes = $node->attributes;
    print scalar @attributes, " properties set for $name.\n";
    foreach $attr ( @attributes ) {
        # check if the attribute is an attached property
        if ( $attr->nodeName =~ /^(.+)\.(.+)/ ) {
            # we have an attached property
            print "\tAttached property: $1::$2 = ", $attr->value, "\n";
            print $file "\t$name->SetValue( &$1::$2, _L(\"", $attr->value, "\") );\n";
        } else {
            # it's not an attached property
            print "\tProperty: ", $attr->nodeName, " = ", $attr->value, "\n";
            print $file "\t$name->", $attr->nodeName, ".ReadValue( _L(\"", $attr->value, "\") );\n";
        }
    }
}

# add control to the container parent
sub addControl {
    my ( $name, $parent, $file ) = @_;
    if ( defined( $parent )) {
        print $file "\t$parent->";
    }
    else {
        print $file "\t";
    }
    print $file "AddControl( $name );\n";
}

# create the control
sub createControl {
    my ( $name, $file ) = @_;
    print $file "\t$name->Create();\n";
}
