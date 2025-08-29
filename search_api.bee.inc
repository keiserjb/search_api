<?php

/**
 * @file
 * Bee commands for SearchAPI.
 */

/**
 * Implements hook_bee_command().
 */
function search_api_bee_command() {
  $items = array();

  $items['search-api-list'] = array(
    'description' => bt('List all search indexes.'),
    'examples' => array(
      'bee searchapi-list' => bt('List all search indexes.'),
      'bee sapi-l' => bt('Alias to list all search indexes.'),
    ),
    'aliases' => array('sapi-l'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_list_cb',
  );

  $items['search-api-enable'] = array(
    'description' => bt('Enable one or all disabled search_api indexes.'),
    'examples' => array(
      'bee searchapi-enable' => bt('Enable all disabled indexes.'),
      'bee sapi-en' => bt('Alias to enable all disabled indexes.'),
      'bee sapi-en 1' => bt('Enable index with the ID !id.', array('!id' => 1)),
    ),
    'arguments' => array(
      'index_id' => bt('The numeric ID or machine name of an index to enable.'),
    ),
    'aliases' => array('sapi-en'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_enable_cb',
  );

  $items['search-api-disable'] = array(
    'description' => bt('Disable one or all enabled search_api indexes.'),
    'examples' => array(
      'bee searchapi-disable' => bt('Disable all enabled indexes.'),
      'bee sapi-dis' => bt('Alias to disable all enabled indexes.'),
      'bee sapi-dis 1' => bt('Disable index with the ID !id.', array('!id' => 1)),
    ),
    'arguments' => array(
      'index_id' => bt('The numeric ID or machine name of an index to disable.'),
    ),
    'aliases' => array('sapi-dis'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_disable_cb',
  );

  $items['search-api-status'] = array(
    'description' => bt('Show the status of one or all search indexes.'),
    'examples' => array(
      'bee searchapi-status' => bt('Show the status of all search indexes.'),
      'bee sapi-s' => bt('Alias to show the status of all search indexes.'),
      'bee sapi-s 1' => bt('Show the status of the search index with the ID !id.', array('!id' => 1)),
      'bee sapi-s default_node_index' => bt('Show the status of the search index with the machine name !name.', array('!name' => 'default_node_index')),
    ),
    'aliases' => array('sapi-s'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_status_cb',
  );

  $items['search-api-index'] = array(
    'description' => bt('Index items for one or all enabled search_api indexes. Optional parameters: limit (number of items to index, defaults to all), batch_size (items per batch, defaults to index cron limit).'),
    'examples' => array(
      'bee search-api-index' => bt('Index items for all enabled indexes.'),
      'bee sapi-i' => bt('Alias to index items for all enabled indexes.'),
      'bee sapi-i 1' => bt('Index items for the index with the ID !id.', array('!id' => 1)),
      'bee sapi-i default_node_index' => bt('Index items for the index with the machine name !name.', array('!name' => 'default_node_index')),
      'bee sapi-i 1 100' => bt("Index a maximum number of !limit items (index's cron batch size items per batch run) for the index with the ID !id.", array('!limit' => 100, '!id' => 1)),
      'bee sapi-i 1 100 10' => bt("Index a maximum number of !limit items (!batch_size items per batch run) for the index with the ID !id.", array('!limit' => 100, '!batch_size' => 10, '!id' => 1)),
      'bee sapi-i 0 0 100' => bt("Index all items of all indexes with !batch_size items per batch run.", array('!batch_size' => 100)),
    ),
    'aliases' => array('sapi-i'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_index_cb',
  );

  $items['search-api-reindex'] = array(
    'description' => bt('Force reindexing of one or all search indexes, without clearing existing index data.'),
    'examples' => array(
      'bee searchapi-reindex' => bt('Schedule all search indexes for reindexing.'),
      'bee sapi-r' => bt('Alias to schedule all search indexes for reindexing .'),
      'bee sapi-r 1' => bt('Schedule the search index with the ID !id for re-indexing.', array('!id' => 1)),
      'bee sapi-r default_node_index' => bt('Schedule the search index with the machine name !name for re-indexing.', array('!name' => 'default_node_index')),
    ),
    'arguments' => array(
      'index_id' => bt('The numeric ID or machine name of an index.'),
    ),
    'aliases' => array('sapi-r'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_reindex_cb',
  );

  $items['search-api-reindex-items'] = array(
    'description' => bt('Force re-indexing of one or more specific items.'),
    'examples' => array(
      'bee search-api-reindex-items node 12,34,56' => bt('Schedule the nodes with ID 12, 34 and 56 for re-indexing.'),
    ),
    'arguments' => array(
      'entity_type' => bt('The entity type whose items should be re-indexed.'),
      'entities' => bt('The entities of the given entity type to be re-indexed.'),
    ),
    'aliases' => array('sapi-ri'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_reindex_items_cb',
  );

  $items['search-api-clear'] = array(
    'description' => bt('Clear one or all search indexes and mark them for re-indexing.'),
    'examples' => array(
      'bee searchapi-clear' => bt('Clear all search indexes.'),
      'bee sapi-c' => bt('Alias to clear all search indexes.'),
      'bee sapi-c 1' => bt('Clear the search index with the ID !id.', array('!id' => 1)),
      'bee sapi-c default_node_index' => bt('Clear the search index with the machine name !name.', array('!name' => 'default_node_index')),
    ),
    'arguments' => array(
      'index_id' => bt('The numeric ID or machine name of an index.'),
    ),
    'aliases' => array('sapi-c'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_clear_cb',
  );

  $items['search-api-execute-tasks'] = array(
    'description' => bt('Execute all pending tasks or all for a given server.'),
    'examples' => array(
      'bee search-api-execute-tasks my_solr_server' => bt('Execute all pending tasks on !server', array('!server' => 'my_solr_server')),
      'bee sapi-et my_solr_server' => bt('Execute all pending tasks on !server', array('!server' => 'my_solr_server')),
      'bee sapi-et' => bt('Execute all pending tasks on all servers.'),
    ),
    'arguments' => array(
      'server_id' => bt('The numeric ID or machine name of a server to execute tasks on.'),
    ),
    'aliases' => array('sapi-et'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_execute_tasks_cb',
  );

  $items['search-api-set-index-server'] = array(
    'description' => bt('Set the search server used by a given index.'),
    'examples' => array(
      'bee search-api-set-index-server default_node_index my_solr_server' => bt('Set the !index index to use the !server server.', array('!index' => 'default_node_index', '!server' => 'my_solr_server')),
      'bee sapi-sis default_node_index my_solr_server' => bt('Alias to set the !index index to use the !server server.', array('!index' => 'default_node_index', '!server' => 'my_solr_server')),
    ),
    'arguments' => array(
      'index_id' => bt('The numeric ID or machine name of an index.'),
      'server_id' => bt('The numeric ID or machine name of a server to set on the index.'),
    ),
    'aliases' => array('sapi-sis'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_set_index_server_cb',
  );

  $items['search-api-server-list'] = array(
    'description' => bt('List all search servers.'),
    'examples' => array(
      'bee search-api-server-list' => bt('List all search servers.'),
      'bee sapi-sl' => bt('Alias to list all search servers.'),
    ),
    'aliases' => array('sapi-sl'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_server_list_cb',
  );

  $items['search-api-server-enable'] = array(
    'description' => bt('Enable a search server.'),
    'examples' => array(
      'bee search-api-server-enable my_solr_server' => bt('Enable the !server search server.', array('!server' => 'my_solr_server')),
      'bee sapi-se my_solr_server' => bt('Alias to enable the !server search server.', array('!server' => 'my_solr_server')),
    ),
    'arguments' => array(
      'server_id' => bt('The numeric ID or machine name of a search server to enable.'),
    ),
    'aliases' => array('sapi-se'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_server_enable_cb',
  );

  $items['search-api-server-disable'] = array(
    'description' => bt('Disable a search server.'),
    'examples' => array(
      'bee search-api-server-disable my_solr_server' => bt('Disable the !server search server.', array('!server' => 'my_solr_server')),
      'bee sapi-sd my_solr_server' => bt('Alias to disable the !server search server.', array('!server' => 'my_solr_server')),
    ),
    'arguments' => array(
      'server_id' => bt('The numeric ID or machine name of a search server to disable.'),
    ),
    'aliases' => array('sapi-sd'),
    'bootstrap' => BACKDROP_BOOTSTRAP_FULL,
    'callback' => 'search_api_server_disable_cb',
  );

  return $items;
}


/**
 * List all search indexes.
 */
function bee_search_api_list() {
  if (search_api_bee_static(__FUNCTION__)) { return; }

  $indexes = search_api_index_load_multiple(FALSE);
  if (empty($indexes)) {
    bee_message(bt('There are no indexes present.'));
    return;
  }

  $table = array(
    'header' => array(
      array('value' => bt('Id')),
      array('value' => bt('Name')),
      array('value' => bt('Index')),
      array('value' => bt('Server')),
      array('value' => bt('Type')),
      array('value' => bt('Status')),
      array('value' => bt('Limit')),
    ),
    'rows' => array(),
  );

  foreach ($indexes as $index) {
    $type_info = search_api_get_item_type_info($index->item_type);
    $type = isset($type_info['name']) ? $type_info['name'] : $index->item_type;

    try {
      $server_obj = $index->server();
      $server = $server_obj ? $server_obj->name : '(' . bt('none') . ')';
    }
    catch (SearchApiException $e) {
      watchdog_exception('search_api', $e);
      $server = '(' . bt('unknown: !server', array('server' => $index->server)) . ')';
    }

    $table['rows'][] = array(
      array('value' => (string) $index->id),
      array('value' => (string) $index->name),
      array('value' => (string) $index->machine_name),
      array('value' => (string) $server),
      array('value' => (string) $type),
      array('value' => $index->enabled ? bt('enabled') : bt('disabled')),
      array('value' => isset($index->options['cron_limit']) ? (string) $index->options['cron_limit'] : ''),
    );
  }

  bee_render_table($table);
}

/**
 * Enable index(es).
 *
 * @param string|integer $index_id
 *   The index name or id which should be enabled.
 */
function bee_search_api_enable($index_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  $indexes = search_api_bee_get_index($index_id);
  if (empty($indexes)) {
    return;
  }
  foreach ($indexes as $index) {
    $vars = array('!index' => $index->name);
    if (!$index->enabled) {
      bee_message(bt("Enabling index !index and queueing items for indexing.", $vars), 'notice');
      $success = FALSE;
      try {
        if ($success = search_api_index_enable($index->id)) {
          bee_message(bt("The index !index was successfully enabled.", $vars), 'ok');
        }
      }
      catch (SearchApiException $e) {
        bee_message($e->getMessage(), 'error');
      }
      if (!$success) {
        bee_message(bt("Error enabling index !index.", $vars), 'error');
      }
    }
    else {
      bee_message(bt("The index !index is already enabled.", $vars), 'error');
    }
  }
}

/**
 * Disable index(es).
 *
 * @param string|integer $index_id
 *   The index name or id which should be disabled.
 */
function bee_search_api_disable($index_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  $indexes = search_api_bee_get_index($index_id);
  if (empty($indexes)) {
    return;
  }
  foreach ($indexes as $index) {
    $vars = array('!index' => $index->name);
    if ($index->enabled) {
      $success = FALSE;
      try {
        if ($success = search_api_index_disable($index->id)) {
          bee_message(bt("The index !index was successfully disabled.", $vars), 'ok');
        }
      }
      catch (SearchApiException $e) {
        bee_message($e->getMessage(), 'error');
      }
      if (!$success) {
        bee_message(bt("Error disabling index !index.", $vars), 'error');
      }
    }
    else {
      bee_message(bt("The index !index is already disabled.", $vars), 'error');
    }
  }
}

/**
 * Display index status.
 */
function bee_search_api_status($index_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  $indexes = search_api_bee_get_index($index_id);
  if (empty($indexes)) {
    return;
  }
  // See search_api_index_status()
  $table = array(
    'header' => array(
      array('value' => bt('Id')),
      array('value' => bt('Index')),
      array('value' => bt('% Complete')),
      array('value' => bt('Indexed')),
      array('value' => bt('Total')),
    ),
    'rows' => array(),
  );

  foreach ($indexes as $index) {
    $status = search_api_index_status($index);
    $complete = ($status['total'] > 0) ? 100 * round($status['indexed'] / $status['total'], 3) . '%' : '-';
    $table['rows'][] = array(
      array('value' => (string) $index->id),
      array('value' => (string) $index->name),
      array('value' => (string) $complete),
      array('value' => (string) $status['indexed']),
      array('value' => (string) $status['total']),
    );
  }

  bee_render_table($table);
}

/**
 * Index items.
 *
 * @param string|integer $index_id
 *   The index name or id for which items should be indexed.
 * @param integer $limit
 *   Maximum number of items to index.
 * @param integer $batch_size
 *   Number of items to index per batch.
 */
function bee_search_api_index($index_id = NULL, $limit = NULL, $batch_size = NULL) {
  // If this guard is killing the run, comment it out while testing.
  if (function_exists('search_api_bee_static') && search_api_bee_static(__FUNCTION__)) {
    return;
  }

  $indexes = search_api_bee_get_index(!empty($index_id) ? $index_id : NULL);
  if (empty($indexes)) {
    bee_message('No indexes found.', 'warning'); echo "No indexes found.\n"; @ob_flush(); flush();
    return;
  }

  foreach ($indexes as $index) {
    _bee_search_api_batch_indexing_create($index, $limit, $batch_size);
  }
}

/**
 * Bee "create" now performs indexing immediately (no Batch API handoff).
 */
function _bee_search_api_batch_indexing_create(SearchApiIndex $index, $limit = NULL, $batch_size = NULL) {
  try {
    $datasource = $index->datasource();
  }
  catch (SearchApiException $e) {
    bee_message($e->getMessage(), 'error'); echo $e->getMessage()."\n"; @ob_flush(); flush();
    return FALSE;
  }

  $status    = $datasource->getIndexStatus($index);
  $remaining = max(0, (int) $status['total'] - (int) $status['indexed']);

  if ($remaining <= 0) {
    $msg = bt("The index !index is up to date.", ['!index' => $index->name]);
    bee_message($msg, 'ok'); echo $msg."\n"; @ob_flush(); flush();
    return FALSE;
  }

  // Sizes.
  if (!isset($batch_size)) {
    $batch_size = !empty($index->options['cron_limit']) ? (int) $index->options['cron_limit'] : (int) SEARCH_API_DEFAULT_CRON_LIMIT;
  } else {
    $batch_size = (int) $batch_size;
  }
  if ($batch_size <= 0) { $batch_size = $remaining; }

  if (!isset($limit) || !is_int($limit += 0) || $limit <= 0) { $limit = $remaining; } else { $limit = (int) $limit; }

  $start_msg = bt("Indexing a maximum number of !limit items (!batch_size items per pass) for the index !index.",
    ['!index' => $index->name, '!limit' => $limit, '!batch_size' => $batch_size]);
  bee_message($start_msg, 'ok'); echo $start_msg."\n"; @ob_flush(); flush();

  // Streamed indexing.
  $left  = min($limit, $remaining);
  $total = 0;

  while ($left > 0) {
    $to = min($batch_size, $left);

    // Indexer call (use whichever exists).
    $n = NULL;
    if (function_exists('search_api_index_items')) {
      $n = (int) search_api_index_items($index, $to);
    }
    elseif (method_exists($index, 'indexItems')) {
      $n = (int) $index->indexItems($to);
    }
    else {
      $msg = 'No indexing function/method found (search_api_index_items or $index->indexItems).';
      bee_message($msg, 'error'); echo $msg."\n"; @ob_flush(); flush();
      break;
    }

    $tick = bt('Indexed !n item(s). Left in this run: !left.', ['!n' => $n, '!left' => max(0, $left - $n)]);
    bee_message($tick, $n > 0 ? 'ok' : 'warning'); echo $tick."\n"; @ob_flush(); flush();

    if ($n <= 0) {
      // Nothing more to do (empty tracker / server deferred / miswired indexer).
      break;
    }

    $left  -= $n;
    $total += $n;
  }

  $done = bt('Done. Indexed !n items for !index.', ['!n' => $total, '!index' => $index->name]);
  bee_message($done, 'ok'); echo $done."\n"; @ob_flush(); flush();

  return $total > 0;
}

/**
 * Copy of formal_plural that works with bee as 't' may not be available.
 */
function _search_api_bee_format_plural($count, $singular, $plural, array $args = array(), array $options = array()) {
  $args['@count'] = $count;
  if ($count == 1) {
    return bt($singular, $args, $options);
  }

  // Get the plural index through the gettext formula.
  $index = (function_exists('locale_get_plural')) ? locale_get_plural($count, isset($options['langcode']) ? $options['langcode'] : NULL) : -1;
  // If the index cannot be computed, use the plural as a fallback (which
  // allows for most flexiblity with the replaceable @count value).
  if ($index < 0) {
    return bt($plural, $args, $options);
  }
  else {
    switch ($index) {
      case "0":
        return bt($singular, $args, $options);
      case "1":
        return bt($plural, $args, $options);
      default:
        unset($args['@count']);
        $args['@count[' . $index . ']'] = $count;
        return bt(strtr($plural, array('@count' => '@count[' . $index . ']')), $args, $options);
    }
  }
}

/**
 * Helper function to flush output to ensure real-time feedback in terminal.
 */
function _search_api_bee_flush() {
  // Flush all output buffers
  while (ob_get_level() > 0) {
    ob_end_flush();
  }

  // Force immediate output to terminal
  if (function_exists('flush')) {
    flush();
  }

  // Also try to flush STDOUT and STDERR directly if available
  if (defined('STDOUT')) {
    fflush(STDOUT);
  }
  if (defined('STDERR')) {
    fflush(STDERR);
  }
}

/**
 * Mark for re-indexing.
 */
function bee_search_api_reindex($index_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  $indexes = search_api_bee_get_index($index_id);
  if (empty($indexes)) {
    return;
  }
  // See search_api_index_reindex()
  foreach ($indexes as $index) {
    $index->reindex();
    bee_message(bt('!index was successfully marked for re-indexing.', array('!index' => $index->machine_name)), 'ok');
  }
}

/**
 * Marks the given entities as needing to be re-indexed.
 */
function bee_search_api_reindex_items($entity_type, $entities) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }

  // Validate list of entity ids.
  if (!empty($entities) && !preg_match('#^[0-9]*(,[0-9]*)*$#', $entities)) {
    bee_message(bt('Entities should be a single numeric entity ID or a list with the numeric entity IDs separated by comma.'), 'error');
    return;
  }

  $ids = explode(',', $entities);

  if (!empty($ids)) {
    search_api_track_item_change($entity_type, $ids);

    $combined_ids = array();
    foreach ($ids as $id) {
      $combined_ids[] = $entity_type . '/' . $id;
    }
    search_api_track_item_change('multiple', $combined_ids);
  }
}

/**
 * Clear an index.
 */
function bee_search_api_clear($index_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  $indexes = search_api_bee_get_index($index_id);
  if (empty($indexes)) {
    return;
  }
  // See search_api_index_reindex()
  foreach ($indexes as $index) {
    $index->clear();
    bee_message(bt('!index was successfully cleared.', array('!index' => $index->machine_name)), 'ok');
  }
}

/**
 * Execute all pending tasks or all for a given server.
 */
function bee_search_api_execute_tasks($server_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }

  // Attempt to load the associated server.
  $server = NULL;
  if ($server_id) {
    $servers = search_api_bee_get_server($server_id);
    if (!$servers) {
      return;
    }
    $server = reset($servers);
  }

  // Process batch op with bee.
  try {
    search_api_execute_pending_tasks($server);
    if ($server) {
      bee_message(bt('!server tasks have been successfully executed.', array('!server' => $server->machine_name ?: 'All')), 'ok');
    }
    else {
      bee_message(bt('All tasks have been successfully executed.'), 'ok');
    }
  }
  catch (SearchApiException $e) {
    bee_message($e->getMessage(), 'error');
  }
}

/**
 * Set the server for a given index.
 */
function bee_search_api_set_index_server($index_id = NULL, $server_id = NULL) {
  if (search_api_bee_static(__FUNCTION__)) {
    return;
  }
  // Make sure we have parameters to work with.
  if (empty($index_id) || empty($server_id)) {
    bee_message(bt('You must specify both an index and server.'), 'error');
    return;
  }
  // Fetch current index and server data.
  $indexes = search_api_bee_get_index($index_id);
  $servers = search_api_bee_get_server($server_id);
  if (empty($indexes) || empty($servers)) {
    // If the specified index or server can't be found, just return. An
    // appropriate error message should have been printed already.
    return;
  }
  // Set the new server on the index.
  $success = FALSE;
  $index = reset($indexes);
  $server = reset($servers);
  try {
    $success = $index->update(array('server' => $server->machine_name));
  }
  catch (SearchApiException $e) {
    bee_message($e->getMessage(), 'error');
  }
  if ($success === FALSE) {
    bee_message(bt('There was an error setting index !index to use server !server.', array('!index' => $index->name, '!server' => $server->name)), 'error');
  }
  elseif (!$success) {
    bee_message(bt('Index !index was already using server !server.', array('!index' => $index->name, '!server' => $server->name)), 'ok');
  }
  else {
    bee_message(bt('Index !index has been set to use server !server and items have been queued for indexing.', array('!index' => $index->name, '!server' => $server->name)), 'ok');
  }
}

/**
 * Returns an index or all indexes as an array.
 *
 * @param string|int|null $index_id
 *   (optional) The ID or machine name of the index to load. Defaults to
 *   loading all available indexes.
 *
 * @return SearchApiIndex[]
 *   An array of indexes.
 */
function search_api_bee_get_index($index_id = NULL) {
  $ids = ($index_id === NULL) ? FALSE : array($index_id); // FALSE => load all
  $indexes = search_api_index_load_multiple($ids);
  if (empty($indexes)) {
    bee_message(bt('Invalid index_id or no indexes present. Listing all indexes:'));
    bee_message();
    bee_search_api_list();
  }
  return $indexes;
}

/**
 * Returns a server or all servers as an array.
 *
 * @param string|int|null $server_id
 *   (optional) The ID or machine name of the server to load. Defaults to
 *   loading all available servers.
 *
 * @return SearchApiServer[]
 *   An array of servers.
 */
function search_api_bee_get_server($server_id = NULL) {
  $ids = ($server_id === NULL) ? FALSE : array($server_id);
  return search_api_server_load_multiple($ids);
}

/**
 * Does a static lookup to prevent Drush 4 from running twice.
 *
 * @param string $function
 *   The Drush function being called.
 *
 * @return bool
 *   TRUE if the function was already called in this Drush execution, FALSE
 *   otherwise.
 *
 * @see http://drupal.org/node/704848
 */
function search_api_bee_static($function) {
  static $index = array();
  if (isset($index[$function])) {
    return TRUE;
  }
  $index[$function] = TRUE;
  return FALSE;
}

/**
 * Lists all search servers.
 */
function bee_search_api_server_list() {
  if (search_api_bee_static(__FUNCTION__)) { return; }

  $servers = search_api_server_load_multiple(FALSE);
  if (empty($servers)) {
    bee_message(bt('There are no servers present.'));
    return;
  }

  $table = array(
    'header' => array(
      array('value' => bt('Machine name')),
      array('value' => bt('Name')),
      array('value' => bt('Status')),
    ),
    'rows' => array(),
  );

  foreach ($servers as $server) {
    $table['rows'][] = array(
      array('value' => (string) $server->machine_name),
      array('value' => (string) $server->name),
      array('value' => $server->enabled ? bt('enabled') : bt('disabled')),
    );
  }

  bee_render_table($table);
}

/**
 * Enables a search server.
 *
 * @param int|string $server_id
 *   The numeric ID or machine name of the server to enable.
 */
function bee_search_api_server_enable($server_id = NULL) {
  if (!isset($server_id)) {
    bee_message(bt('Please provide a valid server id.'));
    return;
  }
  $server = search_api_server_load($server_id);
  if (empty($server)) {
    bee_message(bt('The server was not able to load.'));
    return;
  }
  else {
    $server->update(array('enabled' => 1));
    bee_message(bt('The server was enabled successfully.'));
  }
}

/**
 * Disables a search server.
 *
 * @param int|string $server_id
 *   The numeric ID or machine name of the server to disable.
 */
function bee_search_api_server_disable($server_id = NULL) {
  if (!isset($server_id)) {
    bee_message(bt('Please provide a valid server id.'));
    return;
  }
  $server = search_api_server_load($server_id);
  if (empty($server)) {
    bee_message(bt('The server was not able to load.'));
  }
  else {
    $server->update(array('enabled' => 0));
    bee_message(bt('The server was disabled successfully.'));
  }
}

// Tiny helper to read an argument by name or position.
function _sapi_arg(array $arguments, $name, $pos, $default = NULL) {
  if (array_key_exists($name, $arguments)) return $arguments[$name];
  if (array_key_exists($pos,  $arguments)) return $arguments[$pos];
  return $default;
}

/** Callbacks wired in hook_bee_command() **/
function search_api_list_cb(array $arguments, array $options) {
  return bee_search_api_list();
}

function search_api_enable_cb(array $arguments, array $options) {
  $index_id = _sapi_arg($arguments, 'index_id', 0, NULL);
  return bee_search_api_enable($index_id);
}

function search_api_disable_cb(array $arguments, array $options) {
  $index_id = _sapi_arg($arguments, 'index_id', 0, NULL);
  return bee_search_api_disable($index_id);
}

function search_api_status_cb(array $arguments, array $options) {
  $index_id = _sapi_arg($arguments, 'index_id', 0, NULL); // NULL => all
  return bee_search_api_status($index_id);
}

function search_api_index_cb(array $arguments, array $options) {
  $index_id   = _sapi_arg($arguments, 'index_id',   0, NULL);
  // Make limit truly optional by defaulting to NULL when not provided
  // This will let the bee_search_api_index function handle it appropriately
  $limit      = array_key_exists('limit', $arguments) || array_key_exists(1, $arguments)
    ? _sapi_arg($arguments, 'limit', 1, NULL)
    : NULL;
  $batch_size = array_key_exists('batch_size', $arguments) || array_key_exists(2, $arguments)
    ? _sapi_arg($arguments, 'batch_size', 2, NULL)
    : NULL;
  return bee_search_api_index($index_id, $limit, $batch_size);
}


function search_api_reindex_cb(array $arguments, array $options) {
  $index_id = _sapi_arg($arguments, 'index_id', 0, NULL);
  return bee_search_api_reindex($index_id);
}

function search_api_reindex_items_cb(array $arguments, array $options) {
  $entity_type = _sapi_arg($arguments, 'entity_type', 0, NULL);
  $entities    = _sapi_arg($arguments, 'entities',    1, NULL);
  return bee_search_api_reindex_items($entity_type, $entities);
}

function search_api_clear_cb(array $arguments, array $options) {
  $index_id = _sapi_arg($arguments, 'index_id', 0, NULL);
  return bee_search_api_clear($index_id);
}

function search_api_execute_tasks_cb(array $arguments, array $options) {
  $server_id = _sapi_arg($arguments, 'server_id', 0, NULL);
  return bee_search_api_execute_tasks($server_id);
}

function search_api_set_index_server_cb(array $arguments, array $options) {
  $index_id  = _sapi_arg($arguments, 'index_id',  0, NULL);
  $server_id = _sapi_arg($arguments, 'server_id', 1, NULL);
  return bee_search_api_set_index_server($index_id, $server_id);
}

function search_api_server_list_cb(array $arguments, array $options) {
  return bee_search_api_server_list();
}

function search_api_server_enable_cb(array $arguments, array $options) {
  $server_id = _sapi_arg($arguments, 'server_id', 0, NULL);
  return bee_search_api_server_enable($server_id);
}

function search_api_server_disable_cb(array $arguments, array $options) {
  $server_id = _sapi_arg($arguments, 'server_id', 0, NULL);
  return bee_search_api_server_disable($server_id);
}
