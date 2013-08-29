<?php

function crashaw_body(){
    
}

function crashaw_fields(){
    return array(
        'crashaw_purporse' => array(
            'field_name' => 'crashaw_purporse', 
            'type' => 'text',
            'cardinality' => 1)
        ,'crashaw_terms' => array(
            'field_name' => 'crashaw_terms', 
            'type' => 'taxonomy_term_reference',
            'cardinality' => -1)        
    );
}

function crashaw_fields_instances(){
    return array(
        'crashaw_purpose' => array(
               'field_name' => 'crashaw_purporse', 
                
        )
    );
}

function crashaw_vocabulary(){
    
}
