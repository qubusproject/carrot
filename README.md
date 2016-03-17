carrot is a C++ library for rendering expressive diagnostic messages.

## Features

* Fully composable

    Have you ever wanted to aggregate diagnostic messages from different
    parts of your software into readable messages without ugly string manipulation
    hacks?

    carrot has you covered. The building blocks of a carrot message are fully
    composable and first-class citizens.

* Semantic messages

    A certain representation of your message might not be suitable for all
    output devices. carrot gives you the ability to declare the intended
    semantic of certain parts of the message. Want to emphasise a word.
    Simply mark it as such.

    Fine-grained formating is still possible for those needing full control.

## FAQ

* Why is the library named carrot?

    The name is a pun on the caret symbol `^` which is used frequently in
    diagnostic messages to mark locations of interest.

* Does carrot support colored output?

    Yes. This is limited to devices supporting colored output, though.

* Does carrot support dynamic content?

    Not yet. One of the main goals of carrot is that the generated
    messages can be displayed on as many output devices as possible.
    Since not all devices support dynamic output, care must be taken
    not to compromise this goal. Optional dynamic content for some devices
    with reasonable static fallbacks for others might be a nice feature for future
    releases.