Problem: If I delete a file that is unsaved and press discard, I get stuck in a dark blue grey screen. Probably some weird state bug.

Look at how file deletion and unsaved state are handled.

Check the UnsavedPrompt component to understand the discard flow.

Check what Canvas renders when there's no active file or trace data.

Check the ConfirmPrompt component and look for how the delete button interacts with unsaved state more carefully.

When you delete an unsaved file and click Discard, handlePromptDiscard calls handleDiscardActive() (which drops/reverts the file) AND
THEN doDelete(). For a never-saved file, handleDiscardActive already removes it, leaving doDelete as a no-op. This double-operation on the same file
creates a bad state.

Delete flow must skip the redundant discard step.