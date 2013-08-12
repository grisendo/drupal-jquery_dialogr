(function($) {

  Drupal.behaviors.jqueryDialogrBlocks = {
    attach: function(context, settings) {
      $('.jquery-dialogr-box:not(.dialogr-processed)', context).each(
        function() {
          var $this = $(this);
          var $classes = $this.attr('class');
          $this.addClass('dialogr-processed');
          var $block_id = $classes.match(/jdb-settings--([a-zA-Z0-9\-\_]+)/g)[0];
          $block_id = $block_id.replace('jdb-settings--', '');
          $dialogr = $this.find('>.content');
          var $title = $('>h2', $this);
          var $subject = $title.text();
          var $a = $('<a></a>');
          $a.text($subject);
          $a.attr('href', '#');
          $title.empty();
          $title.append($a);
          $dialogr.attr('title', $subject);
          $dialogr.dialogr(settings.jquery_dialogr_blocks[$block_id]);
          $($a).bind(
            'click',
            function() {
              $dialogr.dialogr('open');
              return false;
            }
          );
        }
      );
    }
  };

})(jQuery);
