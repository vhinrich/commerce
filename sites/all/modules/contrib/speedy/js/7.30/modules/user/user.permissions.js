(function(e){Drupal.behaviors.permissions={attach:function(t){var n=this;e("table#permissions").once("permissions",function(){var t=e(this);if(t.prev().length)var r=t.prev(),i="after";else var r=t.parent(),i="append";t.detach();var s=e('<input type="checkbox" class="dummy-checkbox" disabled="disabled" checked="checked" />').attr("title",Drupal.t("This permission is inherited from the authenticated user role.")).hide();e("input[type=checkbox]",this).not(".rid-2, .rid-1").addClass("real-checkbox").each(function(){s.clone().insertAfter(this)}),e("input[type=checkbox].rid-2",this).bind("click.permissions",n.toggle).each(n.toggle),r[i](t)})},toggle:function(){var t=this,n=e(this).closest("tr");n.find(".real-checkbox").each(function(){this.style.display=t.checked?"none":""}),n.find(".dummy-checkbox").each(function(){this.style.display=t.checked?"":"none"})}}})(jQuery);