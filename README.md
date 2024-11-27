# shutdown-block-reason

Small Node native module to call `ShutdownBlockReasonCreate` and `ShutdownBlockReasonDestroy`.
In couple with recently added `query-session-end` event it allows to prevent the Windows from shutting down
if Electron app is busy for whatever reason (unsaved work, actively doing something very important,
app needs an extended amount of time to shut down gracefully).

```ts
import {
  create as createShutdownBlockReason,
  destroy as destroyShutdownBlockReason
} from "@lordprotector/shutdown-block-reason"

(async () => {
  // create a window...
  
  createShutdownBlockReason(mainWindow.getNativeWindowHandle(), 'Electron application is closing...');
  
  // Handle Windows WM_QUERYENDSESSION signal
  mainWindow.on('query-session-end', (ev: WindowSessionEndEvent) => {
    console.log('query-session-end event received', ev.reasons);
    ev.preventDefault();
    
    // save work...

    destroyShutdownBlockReason(mainWindow.getNativeWindowHandle());    
  });
})();
```
