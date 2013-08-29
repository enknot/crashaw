<?php


function crashaw_main($gate){
    
  drupal_set_title("Debug Module: {$gate}");
  $args = func_get_args();   
  $gate = strtolower((isset($args[0]))?$args[0]:'');
  $arg_list = ($args)?".  Arguments: " . implode(', ', $args):'';
  
  $ret = "You're on the <em style='green' >Clinical Trials</em> debug page: " . date('l jS \of F Y h:i:s A', time()) . $arg_list;
  $full_crashaw_error = "In order to use this debug feature put the module in full debug mode.";
  
  

  
   switch($gate){
       
       case 'node': 
           $ret = node_load(694);
           return crashaw_pre($ret);
       case 'field': 
                  
           $ret = array();
           $ret['instance'] = field_info_instance('node', 'field_article_refrence', 'article');
           $ret['field'] = field_info_field('field_article_refrence');
           
            return crashaw_pre($ret);
           break;
       
       case 'ct_trials':
             module_load_include('inc', 'ct', 'ct.op');
            module_load_include('inc', 'ct', 'ct.remote');
            module_load_include('inc', 'ct', 'ct.trash');
  
           $ret = ct_remote_trials();
           return crashaw_pre($ret);
           break;
       
       case 'ct_thing':
       
    
            node_types_rebuild(); 
//           if(!in_array('ct', array_keys(node_type_get_types()))){
//               throw new Exception('Clincial Trials content type does not exist. Cannot destroy it.');
//               return false;
//           }

           //destroy the content 
          $ret =  $nodes = node_load_multiple(null, array('type' => 'ct'));
           foreach($nodes as $node){
               node_delete($node->nid);
           }    

          //delete content type
           node_type_delete('ct');
           node_types_rebuild();

            $ret = "<pre>" . print_r($res, 1) . "</pre>";
           break;
       
       case 'types':
           $map = field_info_field_map();
           $ret = "<pre>" . print_r($map, 1) . "</pre>";
           break;
       
       case 'fields': 
           module_load_include('inc', 'debug', 'debug.entity');
           foreach(crashaw_fields() as $field){
               field_create_field($field);
           }
           break;
       
       case 'ct':
           
               //get all types  
      if($args[1] == 'build'){
          
        if(in_array('ct', array_keys(node_type_get_types()))){
//            throw new Exception('Clincial Trials content type already exists');
            $ret = "Already made this brah"; break;
        }

        //crate type
          node_type_save(node_type_set_defaults(array(
             'type' => 'ct',
             'name' => t('Clinical Trial'),
             'description' => t('Externally manage content type for the Clincial Research Studies department.'),
             'base' => 'node_content',
             'disabled' => true, 
             'custom' => 1,
             'modified' => FALSE,
             'title_label' => 'Title'
           )));         
         node_types_rebuild();  
             
      }elseif($args[1] == 'destroy'){
          
          
      if(!in_array('ct', array_keys(node_type_get_types()))){
            $ret = "There is no trial"; break;
        }
        
        
        //delete content type
       node_type_delete('ct');
       node_types_rebuild();
       $ret = "destroyed CT content type";
       
      }else{
          $ret = "No command for anything in " . $arg_list;
      }

        
           break;
      
   };
   
    return $ret;
   
}

function crashaw_pre($obj){
    return "<pre>" . print_r($obj, TRUE) . "</pre>";
}