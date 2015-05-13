/**
 * Notification functions.
 */

/**
 * Play notification, if audio-element is present.
 */
function notify()
{
    var notifySound = $("#notify-sound");
    if(notifySound) {
        notifySound.get(0).play();
    }
}

$(function() {
    // Play notification
    notify();
});
