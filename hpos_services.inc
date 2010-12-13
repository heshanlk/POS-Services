<?php

/**
 * @file
 *  Link stripe functionality to services module.
 */
// reseller operations
function hpos_services_get_key_status($key, $owner = NULL, $email = NULL, $mobile = NULL) {
  if (!isset($key)) {
    return services_error('Missing key', 406);
  }

  $result = db_query('SELECT count(*) as key_count FROM {hpos_keys} WHERE pos_key = \'%s\' status = 0', $key);
  $countResult = db_fetch_array($result);
  $count = $countResult['key_count'];
  $return_array["result"] = 5001;
  if ($count == 1) {
    if (db_query('UPDATE {hpos_keys} SET  status = %d WHERE hpos_keys.pos_key = \'%s\'', 1, $key)) {
      $return_array["key_status"] = 1001;
      $return_array["status_message"] = TRUE;
      return $return_array;
    } else {
      $return_array["key_status"] = 2001;
      $return_array["status_message"] = FALSE;
      return $return_array;
    }
  } else {
    $return_array["key_status"] = 2001;
    $return_array["status_message"] = FALSE;
    return $return_array;
  }
  return services_error('internal error', 506);
}

