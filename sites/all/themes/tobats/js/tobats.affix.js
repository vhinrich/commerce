(function($){
	Drupal.behaviors.tobats_affix = {
		attach: function(context, settings){
			$('.pane-commerce-cart-cart').affix({
			    offset: {
			      top: function(){
			      	if($('.pane-system-user-menu').length>0)
			      		return ( $('.pane-system-user-menu').offset().top + $('.pane-system-user-menu').height() );
			      	else
			      		return ( $('.pane-commerce-cart-cart').offset().top + $('.pane-commerce-cart-cart').height() );
			      }
			    }
			 });
		}
	};
})(jQuery);