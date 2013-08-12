<?php

/**
 * @file
 * Administration pages, functions and hooks for jQuery Dialogr Blocks.
 */

/**
 * Auxiliar function for hook_form_FORM_ID_alter().
 */
function _jquery_dialogr_blocks_form_block_admin_configure_alter(&$form, &$form_state, $form_id) {

  $block_id = $form['module']['#value'] . '-' . $form['delta']['#value'];
  $settings = array();
  $value = jquery_dialogr_blocks_is_dialogr($block_id, $settings);
  if ($value && isset($settings['is_dialogr']) && $settings['is_dialogr']) {
    $value = 1;
  }
  else {
    $value = 0;
  }

  $form['visibility']['dialogrblocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dialogr settings'),
    // TO-DO: Change text.
    '#description' => '',
    '#weight' => 65,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'visibility',
    '#tree' => TRUE,
  );

  $form['visibility']['dialogrblocks']['is_dialogr'] = array(
    '#type' => 'select',
    '#title' => t('Use jQuery Dialogr'),
    // TO-DO: Change text.
    '#description' => '',
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    ),
    '#default_value' => $value,
  );

  $config = unserialize($settings['config']);

  $form['visibility']['dialogrblocks']['maximized'] = array(
    '#type' => 'select',
    '#title' => t('Show maximized'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['maximized']) ? $config['maximized'] : TRUE,
  );

  $form['visibility']['dialogrblocks']['minimized'] = array(
    '#type' => 'select',
    '#title' => t('Show minimized'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['minimized']) ? $config['minimized'] : TRUE,
  );

  $form['visibility']['dialogrblocks']['autoOpen'] = array(
    '#type' => 'select',
    '#title' => t('Auto Open'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['autoOpen']) ? $config['autoOpen'] : TRUE,
  );

  $form['visibility']['dialogrblocks']['closeOnEscape'] = array(
    '#type' => 'select',
    '#title' => t('Close on Escape'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['closeOnEscape']) ? $config['closeOnEscape'] : TRUE,
  );

  $form['visibility']['dialogrblocks']['draggable'] = array(
    '#type' => 'select',
    '#title' => t('Draggable'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['draggable']) ? $config['draggable'] : TRUE,
  );

  $form['visibility']['dialogrblocks']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => isset($config['width']) ? $config['width'] : "300",
  );

  $form['visibility']['dialogrblocks']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => isset($config['height']) ? $config['height'] : "auto",
  );

  $form['visibility']['dialogrblocks']['minWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Min Width'),
    '#default_value' => isset($config['minWidth']) ? $config['minWidth'] : "150",
  );

  $form['visibility']['dialogrblocks']['minHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Min Height'),
    '#default_value' => isset($config['minHeight']) ? $config['minHeight'] : "150",
  );

  $form['visibility']['dialogrblocks']['maxWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Width'),
    '#default_value' => isset($config['maxWidth']) ? $config['maxWidth'] : "false",
  );

  $form['visibility']['dialogrblocks']['maxHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Height'),
    '#default_value' => isset($config['maxHeight']) ? $config['maxHeight'] : "false",
  );

  $form['visibility']['dialogrblocks']['modal'] = array(
    '#type' => 'select',
    '#title' => t('Modal'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['modal']) ? $config['modal'] : FALSE,
  );

  $form['visibility']['dialogrblocks']['resizable'] = array(
    '#type' => 'select',
    '#title' => t('Resizable'),
    '#options' => array(
      FALSE => t('No'),
      TRUE => t('Yes'),
    ),
    '#default_value' => isset($config['resizable']) ? $config['resizable'] : TRUE,
  );

  // TO-DO: More options: show, hide, title, dialogClass, closeText, position!
  // TO-DO: Remember last position.
  $form['#submit'][] = 'jquery_dialogr_blocks_save_settings';

}

/**
 * Additional submit handler for block settings form.
 * Saves jQuery Dialogr settings for the block.
 */
function jquery_dialogr_blocks_save_settings($form, &$form_state) {

  $extras = array(
    'maximized',
    'minimized',
    'autoOpen',
    'closeOnEscape',
    'draggable',
    'width',
    'height',
    'minWidth',
    'minHeight',
    'maxWidth',
    'maxHeight',
    'modal',
    'resizable',
  );
  $config = array();

  $final_extras = array();
  foreach ($extras as $extra) {
    $final_extras[$extra] = $form_state['values']['dialogrblocks'][$extra];
  }

  db_merge('jquery_dialogr_blocks')
  ->key(
    array(
      'block_id' => $form_state['values']['module'] . '-' . $form_state['values']['delta'],
    )
  )
  ->fields(
    array(
      'is_dialogr' => (int) $form_state['values']['dialogrblocks']['is_dialogr'],
      'config' => serialize($final_extras),
    )
  )
  ->execute();
  jquery_dialogr_blocks_update_cache();

}
