<?php

/**
 * @file
 * Theme template file used to format the reviews page of enabled content
 * types when there are reviews.
 * $variables:
 *  $nid: the node ID of the main node being viewed.
 *  $reviews: array of reviews
 *    $rid: review ID.
 *    $uid: user ID of reviewer.
 *    $review: review text.
 *    $created: timestamp of when the review was created.
 */
  global $user;

  $review = $variables['review'];
  $review_content = unserialize($review->review);
  $review_nid = $review->nid;
  $reviewer_uid = $review->uid;
  $classes = '';

  if ($variables['index'] == 0):
    $classes .= ' first';
  endif;

  if ($variables['index'] == (int) ($variables['total_reviews'] - 1)):
    $classes .= ' last';
  endif;

  if ($variables['index'] % 2 == 1):
    $classes .= ' even';
  else:
    $classes .= ' odd';
  endif;

  if ($review->status == 0):
    $classes .= ' unpublished';
  endif;

?>
<div class="reviews-review <?php print $classes; ?>">
  <a name="review_<?php print $review->rid; ?>"></a>
  <div class="reviews-date-author">
    <span class="date"><?php print format_date($review->created, 'long'); ?></span> <?php print t('by'); ?> <span class="author"><?php print reviews_get_username($review->uid); ?></span>
  </div>
  <div class="reviews-content">
    <?php print check_markup($review_content['value'], $review_content['format']); ?>
  </div>
  <?php if ($user->uid == $reviewer_uid && user_is_logged_in()) { ?>
    <div class="reviews-action-links">
      <?php print l(t('edit'), 'node/' . $review_nid . '/edit-review/' . $review->rid); ?>
    </div>
  <?php } ?>
</div>
