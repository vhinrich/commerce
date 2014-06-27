(function($){
	Drupal.behaviors.tobats_affix = {
		attach: function(context, settings){
			$('.pane-commerce-cart-cart').affix({
			    offset: {
			      top: function(){
			      	return ( $('.pane-system-user-menu').offset().top + $('.pane-system-user-menu').height() );
			      }
			    }
			 });
		}
	};
})(jQuery);